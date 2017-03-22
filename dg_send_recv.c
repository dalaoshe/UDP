/* include dgsendrecv1 */
#include	"unprtt.h"
#include	<setjmp.h>

#define	RTT_DEBUG

static struct rtt_info   rttinfo;
static int	rttinit = 0;
static struct control_hdr sendhdr, recvhdr;

static void	sig_alrm(int signo);
static sigjmp_buf	jmpbuf;

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

    sendhdr.seq++;

    struct unp_in_pktinfo info;

    signal(SIGALRM, sig_alrm);
    rtt_newpack(&rttinfo);		/* initialize for this packet */

    sendagain:
#ifdef	RTT_DEBUG
    fprintf(stderr, "send %4d \n: ", sendhdr.seq);

#endif
    sendhdr.ts = rtt_ts(&rttinfo);
    // send request
    Sendto(fd, &sendhdr,sizeof(struct control_hdr), outbuff, outbytes, destaddr, destlen);

    // prepare timer
    struct itimerval tv;
    rtt_start_tv(&tv, &rttinfo);
    // start timer
    setitimer(ITIMER_REAL, &tv, NULL);

    //printf("start timer %d\n",tv.it_value.tv_sec);
#ifdef	RTT_DEBUG
    rtt_debug(&rttinfo);
#endif

    if (sigsetjmp(jmpbuf, 1) != 0) {
        if (rtt_timeout(&rttinfo) < 0) {
            printf("dg_send_recv: no response from server, giving up\n");
            rttinit = 0;	/* reinit in case we're called again */
            errno = ETIMEDOUT;
            return(-1);
        }
#ifdef	RTT_DEBUG
        printf("dg_send_recv: timeout, retransmitting\n");
#endif
        goto sendagain;
    }
    do {
        int flags = 0;
        printf("recv wait\n");
        n = Recvfrom_flags(fd, &recvhdr, sizeof(recvhdr), inbuff, inbytes, &flags, NULL, NULL, &info);


#ifdef	RTT_DEBUG
        printf("recv seq %4d\n", recvhdr.seq);
#endif
    } while (n < sizeof(struct control_hdr) || recvhdr.seq != sendhdr.seq);
    // cancel timer
    tv.it_value.tv_sec = tv.it_value.tv_usec = 0;
    tv.it_interval = tv.it_value;
    setitimer(ITIMER_REAL, &tv, NULL);
    rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);

    return(n - sizeof(struct control_hdr));	/* return size of received datagram */
}

static void
sig_alrm(int signo)
{
    printf("time out\n");
    siglongjmp(jmpbuf, 1);
}
/* end dgsendrecv2 */

ssize_t
Dg_send_recv(int fd,
             void *outbuff, size_t outbytes,
             void *inbuff, size_t inbytes,
             SA *destaddr, socklen_t destlen)
{
    ssize_t	n;
    n = dg_send_recv(fd, outbuff, outbytes, inbuff, inbytes,
                     destaddr, destlen);
    if (n < 0)
        printf("dg_send_recv error, fail to get recv, give up \n\n");
    return(n);
}
