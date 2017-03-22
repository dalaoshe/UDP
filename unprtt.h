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

ssize_t	Dg_send_recv(int, void *, size_t, void *, size_t,
                         SA *, socklen_t);
uint32_t clientHash(uint32_t tv);
uint32_t serverHash(uint32_t tv);
/* hash */
#define CLIENT_AUTH_MAGIC 1333
#define CLIENT_HASH_MAGIC 23332333
#define SERVER_AUTH_MAGIC 666
#define SERVER_HASH_MAGIC 12345679
#define IDENTIFIER_LEN 10
#define RESPONSE_LEN 10
#define CMD_LEN 10
#define PARAMS_LEN 20
#define CLIENT_POOL_SIZE
#define PI 0
#define GET 0
#define PARAM_P 0x1
#define PARAM_D 0x2
#define PARAM_L 0x3
#define ERROR_CMD 0xff
#define ERROR_IDENTIFIER 0xff
struct control_hdr {
    uint32_t	seq;	/* sequence # */
    uint32_t	ts;		/* timestamp when sent */
    uint32_t    ts_hash;
    uint32_t    magic;  /* magic valid */
    uint16_t    flags;  /* protocol flags */
    uint16_t    offset;  /* maybe divide because exceed the MAX_LEN */
    uint16_t    check_sum; /* authentication */
    uint16_t    type;       /* data type */
};

struct RequestData {
    uint32_t cmd;
    uint32_t identifier;
    u_int8_t param;
};

struct ResponseData {
    uint32_t response_no;
    char data[RESPONSE_LEN];
};
#endif //UDP_UNPRTT_H
