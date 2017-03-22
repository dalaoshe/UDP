//#include "unp.h"
#include "do_server.h"
#include "do_client.h"


int main(int argc, char **argv) {
    if(strcmp(argv[1],"1") == 0) {
        do_server();
    }
    else {
        do_client();
    }
    return 0;
}