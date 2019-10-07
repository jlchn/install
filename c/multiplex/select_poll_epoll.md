One basic concept of Linux (actually Unix) is the rule that everything in Unix/Linux is a file. Each process has a table of file descriptors that point to files, sockets, devices and other operating system objects.

Typical system that works with many IO sources has an initializaion phase and then enter some kind of standby mode – wait for any client to send request and response it.

Simple solution is to create a thread (or process) for each client , block on read until a request is sent and write a response. This is working ok with a small amount of clients but if we want to scale it to hundred of clients, creating a thread for each client is a bad idea.

## IO Multiplexing

### Methods

- select
- poll
- epoll

### Idea of IO Multiplexing

All the above methods serve the same idea: 

- the process creates a set of file descriptors.
- the process tells the kernel what operations it would like to do with each file descriptor (read, write, ..) .
- the process uses one thread to block on one function call until at least one file descriptor requested operation available.

It's very similar to the Producer and Consumer Design Pattern.

### select

> int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

A call to select( ) will block until at least one of the given file descriptors is ready to perform I/O, or until an optionally specified timeout has elapsed


### poll

> int poll (struct pollfd *fds, unsigned int nfds, int timeout);

``` c
struct pollfd {
      int fd;
      short events; 
      short revents;
};
```

### poll vs select

- poll() does not require that the user calculate the value of the highest- numbered file descriptor +1
- poll() is more efficient for large-valued file descriptors. Imagine watching a single file descriptor with the value 900 via select()—the kernel would have to check each bit of each passed-in set, up to the 900th bit. but select( )’s file descriptor sets are statically sized.
- With select( ), the file descriptor sets are reconstructed on return, so each subsequent call must reinitialize them. The poll( ) system call separates the input (events field) from the output (revents field), allowing the array to be reused without change.
- The timeout parameter to select() is undefined on return. Portable code needs to reinitialize it. This is not an issue with pselect()
- select( ) is more portable, as some Unix systems do not support poll()

### epoll

While working with select and poll, we have to manage everything on user space and we send the sets on each call to wait. To add another socket we need to add it to the set and call select/poll again.

Epoll* system calls help us to create and manage the context in the kernel:

- create a context(the parameter is ignored but has to be positive) in the kernel using epoll_create
- add and remove file descriptors to/from the context using epoll_ctl
- only waiting for the context using epoll_wait in the infinite loop

### epoll vs select/poll

- We can add and remove file descriptor while waiting
- epoll_wait returns only the objects with ready file descriptors
- epoll has better performance – O(1) instead of O(n)
- epoll can behave as level triggered or edge triggered (see man page)
- epoll is Linux specific so non portable

### other materials

https://www.ulduzsoft.com/2014/01/select-poll-epoll-practical-difference-for-system-architects/

https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/

https://medium.com/@copyconstruct/the-method-to-epolls-madness-d9d2d6378642

https://blog.csdn.net/u011671986/article/details/79449853
