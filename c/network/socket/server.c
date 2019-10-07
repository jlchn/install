#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "errmsg.h"

int create_sock();
void bind_and_listen(int sock, struct sockaddr_in *, in_port_t);
void receive_and_send(int sock);
int receive_from_remote(int, char *, int);
void send_to_remote(int, char *, int);
int main(int argc, char *args[])
{
    if (argc != 2)
    {
        print_err("parameters", "<server-port>");
    }

    in_port_t port = atoi(args[1]);

    int sock = create_sock();
    struct sockaddr_in server_addr;
    bind_and_listen(sock, &server_addr, port);

    while (1)
    {
        struct sockaddr_in cli_addr;
        socklen_t cli_addr_len = sizeof(cli_addr);

        int cli_sock = accept(sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (cli_sock < 0)
        {
            print_sys_err("accept() failed");
        }

        char cli_name[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, cli_name, sizeof(cli_name)) != NULL)
        {
            printf("Handling client %s/%d\n", cli_name, ntohs(cli_addr.sin_port));
        }
        else
        {
            puts("Unable to get client address");
        }

        receive_and_send(cli_sock);
    }

    close(sock);

    exit(0);
}

int create_sock()
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0)
    {
        print_sys_err("failed to create the socket");
    }
    return sock;
}

void bind_and_listen(int sock, struct sockaddr_in *sockaddr, in_port_t port)
{

    memset(sockaddr, 0, sizeof(*sockaddr)); // initialization
    (*sockaddr).sin_family = AF_INET;
    (*sockaddr).sin_port = htons(port);
    (*sockaddr).sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)sockaddr, sizeof(*sockaddr)) < 0)
    {
        print_sys_err("bind() failed");
    }

    if (listen(sock, 5) < 0) //5: length to which the queue of pending connections for sockfd may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.
    {
        print_sys_err("listen() failed");
    }
}

void receive_and_send(int sock)
{
    int received = 0;
    int buf_size = 100;
    char buffer[buf_size];

    received = receive_from_remote(sock, buffer, buf_size);

    while (received > 0)
    {

        fputs("Sent: ", stdout);
        fputs(buffer, stdout);
        send_to_remote(sock, buffer, received);
        received = receive_from_remote(sock, buffer, buf_size);
    }
    fputc('\n', stdout);
    close(sock);
}

int receive_from_remote(int sock, char *buffer, int buf_size)
{
    int received = recv(sock, buffer, buf_size, 0);
    if (received < 0)
    {
        print_sys_err("recv() failed");
    }

    return received;
}
void send_to_remote(int sock, char *msg, int msg_len)
{

    ssize_t bytes_sent = send(sock, msg, msg_len, 0);

    if (bytes_sent < 0)
    {
        print_sys_err("failed to send messages");
    }
    else if (bytes_sent != msg_len)
    {
        print_err("send()", "unexpected numbers of bytes sent");
    }
}