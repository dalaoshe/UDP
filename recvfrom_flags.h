//
// Created by dalaoshe on 17-3-20.
//

#ifndef UDP_RECVFROM_FLAGS_H
#define UDP_RECVFROM_FLAGS_H

#include "unp.h"
ssize_t
Recvfrom_flags(int fd,struct control_hdr* recv_hdr, void *ptr, size_t nbytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp);
ssize_t
Sendto_flags(int fd,struct control_hdr* recv_hdr, void *ptr, size_t nbytes, int *flagsp,
               SA *sa, socklen_t salenptr);
#endif //UDP_RECVFROM_FLAGS_H
