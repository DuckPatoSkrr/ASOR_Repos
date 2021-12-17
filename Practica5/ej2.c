//VENTURA MATEOS PEREZ
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

int socketSetup(char * host, char * serv){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(host, serv, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

    if (getnameinfo(result->ai_addr, result->ai_addrlen, hbuf, sizeof(hbuf), sbuf,
                sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
        printf("host=%s, serv=%s\n", hbuf, sbuf);


    freeaddrinfo(result);           /* No longer needed */

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    return sfd;
}

void hora(char * buf){
    time_t aux = time(NULL);
    struct tm *timer = localtime(&aux);
    sprintf(buf,"%0d:%0d:%0d",timer->tm_hour,timer->tm_min,timer->tm_sec);
}

void fecha(char * buf){
    time_t aux = time(NULL);
    struct tm *timer = localtime(&aux);
    sprintf(buf,"%0d:%0d:%0d",timer->tm_mday,timer->tm_mon,timer->tm_year);
}


void timeServer(int sfd){
    char buf[255];
    struct sockaddr  who_addr;
    socklen_t who_addrlen;

    while(1){
        recvfrom(sfd,buf,255,0,&who_addr,&who_addrlen);

        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

        if (getnameinfo(&who_addr, who_addrlen, hbuf, sizeof(hbuf), sbuf,
                    sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
            printf("host=%s, serv=%s\n", hbuf, sbuf);

        switch (buf[0])
        {
        case 't':
            hora(buf);
            break;
        case 'd':
            fecha(buf);
            break;
        case 'q':
            return;

        default:
            continue;
        }
        sendto(sfd,buf,strlen(buf),0,&who_addr,who_addrlen);
    }

}

int main(int argc, char* argv[]){
    
    if(argc != 3){
        printf("Usage: ./ej2 <ip> <port>\n");
        return -1;
    }

    int sfd = socketSetup(argv[1],argv[2]);

    timeServer(sfd);

    close(sfd);
    
    return 0;
}