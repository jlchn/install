#include <stdio.h>
#include <stdlib.h>

void print_err(const char *msg, const char *detail)
{
    fputs(msg, stderr);
    fputs(": ", stderr);
    fputs(detail, stderr);
    fputc('\n', stderr);
    exit(1);
}

void print_sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}