#include "uart.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(6789);
    addr.sin_addr.s_addr = inet_addr("131.123.35.13");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if( sock < 0)
    {
        perror("socket");
        exit(1);
    }

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        close(sock);
        perror("connect");
        exit(2);
    }

    close(sock);
}
