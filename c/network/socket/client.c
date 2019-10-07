#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "errmsg.h"

int create_sock();
void construct_remote_sock_addr(struct sockaddr_in *, char *, in_port_t);
void send_to_remote(int, struct sockaddr_in *, char *, int);
void receive_from_remote(int, int);

int main(int argc, char *args[])
{
    if (argc != 4)
    {
        print_err("parameters", "<server-ip> <server-port> msg");
    }

    char *ip = args[1];
    in_port_t port = atoi(args[2]);
    char *msg = args[3];
    size_t msg_len = strlen(msg);

    int sock = create_sock();
    struct sockaddr_in server_addr;
    construct_remote_sock_addr(&server_addr, ip, port);
    send_to_remote(sock, &server_addr, msg, msg_len);
    receive_from_remote(sock, msg_len);
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

void construct_remote_sock_addr(struct sockaddr_in *sockaddr, char *ip, in_port_t port)
{

    memset(sockaddr, 0, sizeof(*sockaddr)); // initialization
    (*sockaddr).sin_family = AF_INET;
    (*sockaddr).sin_port = htons(port);
    int ret = inet_pton(AF_INET, ip, &(*sockaddr).sin_addr.s_addr);

    if (ret == 0)
    {
        print_err("invalid addr string", ip);
    }
    else if (ret < 0)
    {
        print_sys_err("inet_pton failed");
    }
}

void send_to_remote(int sock, struct sockaddr_in *sock_addr, char *msg, int msg_len)
{
    if (connect(sock, (struct sockaddr *)sock_addr, sizeof(*sock_addr)) < 0)
    {
        print_sys_err("failed to connect to remote server");
    }

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

void receive_from_remote(int sock, int msg_len)
{
    int received = 0;
    int total_received = 0;

    fputs("Received: ", stdout);
    int buf_size = 100;
    while (total_received < msg_len)
    {
        char buffer[buf_size];
        received = recv(sock, buffer, buf_size - 1, 0);

        if (received == 0)
        {
            print_err("recv", "connection closed");
        }
        else if (received < 0)
        {
            print_sys_err("recv() failed");
        }

        total_received += received;
        buffer[received] = '\0';
        fputs(buffer, stdout);
    }
    fputc('\n', stdout);
}