//
// Created by dalaoshe on 17-3-20.
//

#ifndef UDP_RECVFROM_FLAGS_H
#define UDP_RECVFROM_FLAGS_H

#include "unp.h"
//class recvfrom_flags {
//
//};
ssize_t
Recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp);
int aas;
int ss;
#endif //UDP_RECVFROM_FLAGS_H
