#include	"unprtt.h"
#include	<setjmp.h>

#define	RTT_DEBUG

static struct rtt_info   rttinfo;
static int	rttinit = 0;
static struct control_hdr sendhdr, recvhdr;

static void	sig_alrm(int signo);
static sigjmp_buf	jmpbuf;

static int check_from_server(struct control_hdr* hdr) {// 基于时间戳的服务器程序验证，
    uint32_t server_auth = serverHash(hdr->ts);
    if(server_auth!= hdr->ts_hash) {
        fprintf(stderr,"not from server, get hash:%u  need hash:%u\n",hdr->ts_hash,server_auth);
        return 0;
    }
    return 1;
}
static int check_recv_seq(struct control_hdr* hdr) {
    if(hdr->seq != sendhdr.seq) {
#ifdef RTT_DEBUG
        printf("hdr->seq != send %d\n",hdr->seq);
#endif
    }
    return hdr->seq == sendhdr.seq;
}
static int check_recv_hdr(struct control_hdr* hdr) {
    int from_server = check_from_server(hdr);
    int no_time_out = checkTimeOut(hdr->ts);
    int valid_seq = check_recv_seq(hdr);
    return from_server && no_time_out && valid_seq;
}
ssize_t
dg_send_recv(int fd,
             void* outbuff, size_t outbytes,
             void *inbuff, size_t inbytes,
             SA *destaddr, socklen_t destlen)
{
    ssize_t			n;

    if (rttinit == 0) {
        rtt_init(&rttinfo);		/* first time we're called */
        rttinit = 1;
        rtt_d_flag = 1;
    }


    struct unp_in_pktinfo info;

    signal(SIGALRM, sig_alrm);
    rtt_newpack(&rttinfo);		/* initialize for this packet */

    sendagain:
    sendhdr.seq++;
#ifdef	RTT_DEBUG
    fprintf(stderr, "send %4d \n: ", sendhdr.seq);
#endif

    sendhdr.ts = time(NULL);
    sendhdr.ts_hash = clientHash(sendhdr.ts);

    // 发送请求数据
    int resp_count = 0, resp_to_recv = 0;
    Sendto(fd, &sendhdr,sizeof(struct control_hdr), outbuff, outbytes, destaddr, destlen);

    // 准备计时器
    struct itimerval tv;
    rtt_start_tv(&tv, &rttinfo);
    // 启动计时器, 以程序实际运行时间为准
    setitimer(ITIMER_REAL, &tv, NULL);

#ifdef	RTT_DEBUG
    rtt_debug(&rttinfo);
#endif

    if (sigsetjmp(jmpbuf, 1) != 0) {
        if (rtt_timeout(&rttinfo) < 0) {
            printf("ERROR: client_send_recv has try max times, but no valid response from server, giving up\n");
            rttinit = 0;	/* reinit in case we're called again */
            errno = ETIMEDOUT;
            return(-1);
        }
#ifdef	RTT_DEBUG
        printf("INFO: client_send_recv, timeout, retransmitting\n");
#endif
        goto sendagain;
    }
    do {
        int flags = 0;
        n = Recvfrom_flags(fd, &recvhdr, sizeof(recvhdr), (char*)inbuff+(resp_count*sizeof(struct ResponseData)), inbytes, &flags, NULL, NULL, &info);
        int check_hdr = check_recv_hdr(&recvhdr);
        if(!check_hdr || n < sizeof(struct control_hdr)) {
            fprintf(stderr, "WARNING: INVALID HDR!!!! DISCARD\n");
            continue;
        }
        resp_to_recv = recvhdr.resp_len;
        resp_count ++;
#ifdef	RTT_DEBUG
        printf("recv seq %4d, reso_no %d , need_resp_num %d\n", recvhdr.seq, resp_count, resp_to_recv);
#endif
    } while (resp_count < resp_to_recv); // 收到的同一个请求seq的回复分组与服务器实际发送的分组数量一致,则接收完毕
    // 取消定时器
    tv.it_value.tv_sec = tv.it_value.tv_usec = 0;
    tv.it_interval = tv.it_value;
    setitimer(ITIMER_REAL, &tv, NULL);
    // 更新超时控制器信息
    rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);

    return resp_to_recv;	/* 返回收到的回复分组数量 */
}

static void
sig_alrm(int signo)
{
    siglongjmp(jmpbuf, 1);
}


// 返回收到的回复分组数量
int Client_send_recv(int fd,
             void *outbuff, size_t outbytes,
             void *inbuff, size_t inbytes,
             SA *destaddr, socklen_t destlen)
{
    ssize_t	n;
    n = dg_send_recv(fd, outbuff, outbytes, inbuff, inbytes,
                     destaddr, destlen);
    if (n < 0)
        printf("ERROR: Dg_send_recv error, fail to get recv, give up \n\n");
    return(n);
}
