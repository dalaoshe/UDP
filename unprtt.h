//
// Created by dalaoshe on 17-3-21.
//

#ifndef UDP_UNPRTT_H
#define UDP_UNPRTT_H

#include	"unp.h"

struct rtt_info {
    float		rtt_rtt;	/* most recent measured RTT, seconds */
    float		rtt_srtt;	/* smoothed RTT estimator, seconds */
    float		rtt_rttvar;	/* smoothed mean deviation, seconds */
    float		rtt_rto;	/* current RTO to use, seconds */
    int		rtt_nrexmt;	/* #times retransmitted: 0, 1, 2, ... */
    uint32_t	rtt_base;	/* #sec since 1/1/1970 at start */
};

#define	RTT_RXTMIN      2	/* min retransmit timeout value, seconds */
#define	RTT_RXTMAX     60	/* max retransmit timeout value, seconds */
#define	RTT_MAXNREXMT 	3	/* max #times to retransmit */

/* function prototypes */
void	 rtt_debug(struct rtt_info *);
void	 rtt_init(struct rtt_info *);
void	 rtt_newpack(struct rtt_info *);
int		 rtt_start(struct rtt_info *);
void	 rtt_stop(struct rtt_info *, uint32_t);
int		 rtt_timeout(struct rtt_info *);
uint32_t rtt_ts(struct rtt_info *);

/* function prototypes */
void	 rtt_debug_tv(struct rtt_info *);
void	 rtt_init_tv(struct rtt_info *);
void	 rtt_newpack_tv(struct rtt_info *);
void
rtt_start_tv(struct itimerval* vt, struct rtt_info *ptr);
void	 rtt_stop_tv(struct rtt_info *, uint32_t);
int		 rtt_timeout_tv(struct rtt_info *);
uint32_t rtt_ts(struct rtt_info *);

extern int	rtt_d_flag;	/* can be set nonzero for addl info */


ssize_t
Recvfrom_flags(int fd,void* recv_hdr, size_t hdr_nbytes, void *ptr, size_t payload_nbytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp);
ssize_t
Sendto(int fd,void* send_hdr, size_t hdr_nbytes, void *ptr, size_t nbytes,
             SA *sa, socklen_t salenptr);

int	Client_send_recv(int, void *, size_t, void *, size_t,
                         SA *, socklen_t);
uint32_t clientHash(uint32_t tv);
uint32_t serverHash(uint32_t tv);
int checkTimeOut(time_t tv);

/* 验证请求/回复包来自合法程序的HASH参数 */
#define CLIENT_AUTH_MAGIC 1333
#define CLIENT_HASH_MAGIC 23332333
#define SERVER_AUTH_MAGIC 666
#define SERVER_HASH_MAGIC 12345679

/* 请求/回复包的参数信息 */
#define IDENTIFIER_LEN 10 // 客户端处理请求常数标识符字符串允许的最大长度
#define RESPONSE_LEN 10    // 每个回复分组所带常数数据的最大byte长度
#define CMD_LEN 10          // 客服端处理请求操作字符串允许的最大长度
#define PARAMS_LEN 20       // 客服端处理请求参数字符串允许的最大长度
/* 请求常数 */
#define PI 0
/* 请求操作 */
#define GET 0

/* 请求常数的相关参数 */
#define PARAM_P 0x1
#define PARAM_D 0x2
#define PARAM_L 0x3

#define ERROR_CMD 0xff         // 错误的请求操作
#define ERROR_IDENTIFIER 0xff  // 错误的请求常数
#define MAX_RESPONSE_PACKET 10 // 一次请求最多的回复分组数量


/* 数据格式 */
struct control_hdr { // 消息头
    uint32_t	seq;	/* 消息序列号 */
    time_t	    ts;		/* 时间戳 */
    uint32_t    rtt_ts; /* 更新rtt */
    uint32_t    ts_hash;/* 时间戳对应的HASH值,验证程序来源 */
    uint16_t    resp_len;  /* 指示回复包一共有几个分组 */
    /* 以下子段尚未用到 */
    uint16_t    flags;  /* 标志位 */
    uint16_t    offset;  /* 偏移量 */
    uint16_t    check_sum; /* 校验和 */
    uint16_t    type;       /* 数据类型 */
};

struct RequestData {
    uint32_t cmd; // 请求操作编码
    uint32_t identifier; // 请求的常数编码
    u_int8_t param; // 请求参数
};

struct ResponseData {
    uint32_t response_no; // 回复的分组id
    char data[RESPONSE_LEN]; // 回复的分组数据
};
#endif //UDP_UNPRTT_H
