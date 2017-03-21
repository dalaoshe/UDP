#include "unp.h"
#include "recvfrom_flags.h"
#include "unprtt.h"

#define SERV_PORT 6666
#define CLIENT_PORT 5555
#define MAX_LEN 4096

int main(int argc, char **argv) {

    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr
    ;
    memset(&servaddr,0,sizeof(servaddr));
    memset(&clientaddr,0,sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(CLIENT_PORT);
    clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);


    //Inet_pton(AF_INET,argv[1], &servaddr.sin_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("ERROR\n");
    }
    if(strcmp(argv[1],"1") == 0) {
        printf("server\n");
        bind(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in));
        int n;
        socklen_t len = sizeof(clientaddr);
        char rev[MAX_LEN];
        char msg[MAX_LEN];
        int flags;
        struct unp_in_pktinfo info;
        while (1) {
            memset(rev,0,MAX_LEN);
            Recvfrom_flags(sockfd, rev, MAX_LEN, &flags, (SA*)&clientaddr, &len, &info);
          //  recvfrom(sockfd, rev, MAX_LEN , 0, (SA*)&clientaddr, &len);
          //  recvmsg()
           //         recv()
            printf("recv client: %s \n",rev);
            strcpy(msg, "server get u msg\n");

            sendto(sockfd, msg, MAX_LEN, 0, (SA*) &clientaddr, len);
            //printf("send: %s \n",cache);

        }
    }
    else {
        printf("client\n");
        int n;
        socklen_t len = sizeof(servaddr);
        connect(sockfd, (SA*) &servaddr, len);
        char rev[MAX_LEN];
        char msg[MAX_LEN]  = "client send u msg\n" ;
        char msg2[MAX_LEN];
        while(1) {
            Dg_send_recv(sockfd, msg, MAX_LEN, rev, MAX_LEN, (SA*)&servaddr, len);
            //write(sockfd, msg, MAX_LEN);
            //sendto(sockfd, msg, MAX_LEN ,0, (SA) &servaddr, len);

           // strcpy(msg2,"another\n");
            //write(sockfd, msg2, MAX_LEN);
            //sendto(sockfd, msg2, MAX_LEN/,0, (SA) &servaddr, len);
            //read(sockfd, rev, MAX_LEN);
           // recvfrom(sockfd, rev, MAX_LEN, 0, NULL, NULL);
            printf("recv server: %s \n", rev);


        }
    }
    return 0;
}