//#include "unp.h"
#include "do_server.h"
#include "unprtt.h"



int main(int argc, char **argv) {

    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    memset(&servaddr,0,sizeof(servaddr));
    memset(&clientaddr,0,sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(CLIENT_PORT);
    clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("ERROR\n");
    }
    if(strcmp(argv[1],"1") == 0) {
        printf("server\n");
        while (1) {
            do_server();
        }
    }
    else {
        printf("client\n");
        socklen_t len = sizeof(servaddr);
        connect(sockfd, (SA*) &servaddr, len);
        char rev[MAX_LEN];
        char msg[MAX_LEN]  = "PI" ;
        while(1) {
            Dg_send_recv(sockfd, msg, MAX_LEN, rev, MAX_LEN, (SA*)&servaddr, len);
            printf("recv server: %lf \n", *((double*)(rev+10)));

        }
    }
    return 0;
}