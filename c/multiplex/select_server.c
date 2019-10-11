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
#define MAXLINE 10

int read_from_client (int filedes)
{
  char buffer[MAXLINE];
  int nbytes;

  bzero(buffer, sizeof(buffer)); 
  nbytes = read (filedes, buffer, MAXLINE);
  if (nbytes < 0)
  {
    perror ("error on read");
    exit (1);
  }
  else if (nbytes == 0)
  {
    fputs("eof", stdout);
    return -1; /* End-of-file. */
  }
  else
  {
    // fputs(buffer, stdout);
    fprintf (stdout, "Server: got message: `%s'\n", buffer);
    write(filedes, (const char*)buffer, nbytes); //nbytes instead of sizeof(buffer)
    read_from_client(filedes);
    return 0;
  }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int main() 
{ 
    int listenfd, connfd = -1, nready; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    socklen_t len; 
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
                read_from_client(connfd);
                close(connfd);
                exit(0); 
            } 
        close(connfd); // close in the parent process
        } 
    } 
} 