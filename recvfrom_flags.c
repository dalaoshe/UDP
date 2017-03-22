//
// Created by dalaoshe on 17-3-20.
//

#include "unprtt.h"

ssize_t
recvfrom_flags(int fd, void* recvhdr, size_t hdr_bytes, void *ptr, size_t payload_bytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp)
{
    struct msghdr	msg;
    struct iovec	recv_iov[2];
    ssize_t			n;

#ifdef	HAVE_MSGHDR_MSG_CONTROL
    struct cmsghdr	*cmptr;
	union {
	  struct cmsghdr	cm;
	  char				control[CMSG_SPACE(sizeof(struct in_addr)) +
								CMSG_SPACE(sizeof(struct unp_in_pktinfo))];
	} control_un;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	msg.msg_flags = 0;
#else
    bzero(&msg, sizeof(msg));	/* make certain msg_accrightslen = 0 */
#endif
    //设置接受消息头
    msg.msg_name = sa;
    if(salenptr != NULL) msg.msg_namelen = *salenptr;
    else msg.msg_namelen = 0;
    //设置接受消息buff
    // [0]消息头
    recv_iov[0].iov_base = recvhdr;
    recv_iov[0].iov_len = hdr_bytes;
    // [1]正式载荷
    recv_iov[1].iov_base = ptr;
    recv_iov[1].iov_len = payload_bytes;
    msg.msg_iov = recv_iov;
    msg.msg_iovlen = 2;
    msg.msg_flags = *flagsp;

    if ( (n = recvmsg(fd, &msg, *flagsp)) < 0) {
        return (n);
    }
    if( salenptr != NULL) {
        *salenptr = msg.msg_namelen;    /* pass back results */
    }
    if (pktp)
        bzero(pktp, sizeof(struct unp_in_pktinfo));	/* 0.0.0.0, i/f = 0 */
/* end recvfrom_flags1 */

   // return n;
///* include recvfrom_flags2 */
#ifndef	HAVE_MSGHDR_MSG_CONTROL
    *flagsp = 0;					/* pass back results */
    return(n);
#else

    *flagsp = msg.msg_flags;		/* pass back results */
	if (msg.msg_controllen < sizeof(struct cmsghdr) ||
		(msg.msg_flags & MSG_CTRUNC) || pktp == NULL)
		return(n);

	for (cmptr = CMSG_FIRSTHDR(&msg); cmptr != NULL;
		 cmptr = CMSG_NXTHDR(&msg, cmptr)) {

#ifdef	IP_RECVDSTADDR
		if (cmptr->cmsg_level == IPPROTO_IP &&
			cmptr->cmsg_type == IP_RECVDSTADDR) {

			memcpy(&pktp->ipi_addr, CMSG_DATA(cmptr),
				   sizeof(struct in_addr));
			continue;
		}
#endif

#ifdef	IP_RECVIF
		if (cmptr->cmsg_level == IPPROTO_IP &&
			cmptr->cmsg_type == IP_RECVIF) {
			struct sockaddr_dl	*sdl;

			sdl = (struct sockaddr_dl *) CMSG_DATA(cmptr);
			pktp->ipi_ifindex = sdl->sdl_index;
			continue;
		}
#endif
		err_quit("unknown ancillary data, len = %d, level = %d, type = %d",
				 cmptr->cmsg_len, cmptr->cmsg_level, cmptr->cmsg_type);
	}
	return(n);
#endif	/* HAVE_MSGHDR_MSG_CONTROL */
}
/* end recvfrom_flags2 */

ssize_t
Recvfrom_flags(int fd,void* recv_hdr, size_t hdr_nbytes, void *ptr, size_t payload_nbytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp)
{
    ssize_t		n = 0;
    n = recvfrom_flags(fd, recv_hdr, hdr_nbytes, ptr, payload_nbytes, flagsp, sa, salenptr, pktp);
    if (n < 0)
        printf("recvfrom_flags error\n");
    if (n == 0)
        printf("recvfrom_flags an empty udp packet\n");
    return(n);
}

ssize_t
Sendto(int fd,void* send_hdr, size_t hdr_nbytes, void *ptr, size_t nbytes,
             SA *sa, socklen_t salenptr) {
    struct msghdr	msg;
    struct iovec	send_iov[2];
    ssize_t			n = 0;
    memset(&msg, 0, sizeof(msg));

    msg.msg_name = sa;
    msg.msg_namelen = salenptr;

    send_iov[0].iov_base = send_hdr;
    send_iov[0].iov_len = hdr_nbytes;
    send_iov[1].iov_base = ptr;
    send_iov[1].iov_len = nbytes;

    msg.msg_iov = send_iov;
    msg.msg_iovlen = 2;
    msg.msg_flags = 0;

    if((n = sendmsg(fd, &msg, 0)) < 0) {
        printf("send error \n");
    }
    if(n == 0) {
        printf("send an empty udp packet\n");
    }
    return n;
}
uint32_t clientHash(uint32_t tv)
{
    uint32_t key = tv;
    for(int i = 0; i < 16; ++i) {
    key = (key << 1) + CLIENT_AUTH_MAGIC;
    }
    key = key % CLIENT_HASH_MAGIC;
    return key;
}

uint32_t serverHash(uint32_t tv)
{
    uint32_t key = tv;
    for(int i = 0; i < 16; ++i) {
        key = (key << 1) + SERVER_AUTH_MAGIC;
    }
    key = key % SERVER_HASH_MAGIC;
    return key;
}