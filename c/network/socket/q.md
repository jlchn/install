'\0' 

ssize_t & size_t

& (*sockaddr).sin_addr.s_addr : & and . priority

htonl


There are four general steps for basic TCP server communication:
1. Create a TCP socket using socket().
2. Assign a port number to the socket with bind().
3. Tell the system to allow connections to be made to that port, using listen().
4. Repeatedly do the following:
• Call accept() to get a new socket for each client connection.
• Communicate with the client via that new socket using send() and recv(). • Close the client connection using close().


For IPv4, use the sockaddr_in structure.
It is important to understand that sockaddr_in is just a more detailed view of the data in a sockaddr structure, tailored to sockets using IPv4. Thus, we can fill in the fields of a sockaddr_in and then cast (a pointer to) it to a (pointer to a) sockaddr and pass it to the socket functions, which look at the sa_family field to learn the actual type, then cast back to the appropriate type.
```
struct sockaddr {
          sa_family_t sa_family;     // Address family (e.g., AF_INET)
          char sa_data[14];          // Family-specific address information
};

struct in_addr {
    uint32_t s_addr;
};
struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};


```

We can convert addresses from printable string to numeric(understand by socket) using the inet_pton() function (pton = printable to numeric): 
```
int inet_pton(int addressFamily, const char *src, void *dst)
const char *inet_ntop(int addressFamily, const void *src, char *dst, socklen_t dstBytes)
```

The flags parameter in both send() and recv() provides a way to change some aspects of the default behavior of the socket call. Setting flags to 0 specifies the default behavior. send() and recv() return the number of bytes sent or received or −1 for failure. (See also Section 6.3.)
Remember: TCP is a byte-stream protocol, so send() boundaries are not preserved. The number of bytes read in a single call to recv on the receiver is not necessarily determined by the number of bytes written by a single call to send(). If you call send() with 3000 bytes, it may take several calls to recv() to get all 3000 bytes, even if you pass a 5000-byte buffer to each recv() call. If you call send() with 100 bytes four times, you might receive all 400 bytes with a single call to recv(). A common mistake when writing TCP socket applications involves assuming that if you write all of the data with one send() you can read it all with one recv().


support ipv6

support domain name