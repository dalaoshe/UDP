//
// Created by dalaoshe on 17-3-20.
//

#ifndef UDP_UNP_H
#define UDP_UNP_H
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include   <stdint.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#define	SA	struct sockaddr
#define SERV_PORT 6666
#define CLIENT_PORT 5555
#define MAX_LEN 4096
struct unp_in_pktinfo {
    struct in_addr	ipi_addr;	/* dst IPv4 address */
    int				ipi_ifindex;/* received interface index */
};

struct control_hdr {
    uint32_t	seq;	/* sequence # */
    uint32_t	ts;		/* timestamp when sent */
};
#endif //UDP_UNP_H
