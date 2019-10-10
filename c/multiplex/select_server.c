#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/select.h>
#define PORT 5000 
#define MAXLINE 1024 

int main() 
{ 
    int listenfd, connfd, nready; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    socklen_t len; 
    const int on = 1; 
    struct sockaddr_in cliaddr, servaddr; 
    void sig_chld(int); 
  
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    listen(listenfd, 10); 
  
    FD_ZERO(&rset); 
  
    while (1) { 
  
        FD_SET(listenfd, &rset); 
        nready = select(listenfd + 1, &rset, NULL, NULL, NULL); 
  
        if (FD_ISSET(listenfd, &rset)) { 
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
            if ((childpid = fork()) == 0) { 
                close(listenfd); 
                bzero(buffer, sizeof(buffer)); 
                printf("Message from client: "); 
                read(connfd, buffer, sizeof(buffer)); 
                puts(buffer); 
                write(connfd, (const char*)buffer, sizeof(buffer)); 
                close(connfd); 
                exit(0); 
            } 
            close(connfd); 
        } 
    } 
} 