//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    if(argc != 2){
        printf("Usage: ./ej1 <ip | name>\n");
        return -1;
    }


    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Datagram socket */
    hints.ai_flags = 0;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    if (getaddrinfo(argv[1], NULL, &hints, &result) != 0) {
        perror("getaddrinfo call failed:");
        return -1;
    }


    for (struct addrinfo * rp = result; rp != NULL; rp = rp->ai_next) {
        char * ip;

        struct sockaddr *addr = rp->ai_addr;     /* input */
        socklen_t addrlen = rp->ai_addrlen;         /* input */
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

        if (getnameinfo(addr, addrlen, hbuf, sizeof(hbuf), sbuf,
                    sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
            printf("host=%s, serv=%s\n", hbuf, sbuf);


        char * protocol;
        switch (rp->ai_protocol)
        {
        case IPPROTO_UDP:
            protocol = "UDP";
            break;
        case IPPROTO_TCP:
            protocol = "TCP";
            break;
        default:
            protocol = "UNDEFINED";
            break;
        }
        char * socket;
        switch (rp->ai_socktype)
        {
        case SOCK_STREAM:
            socket = "STREAM";
            break;
        case SOCK_DGRAM:
            socket = "DGRAM";
            break;
        case SOCK_RAW:
            socket = "RAW";
            break;
        default:
            socket = "UNDEFINED";
            break;
        }
        printf("Protocol:%s, Socket type:%s\n",
                protocol,
                socket);
    }
    

    freeaddrinfo(result);
    
    return 0;
}