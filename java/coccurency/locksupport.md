
### what is locksupport

LockSupport provides an alternative for some of Thread's deprecated methods: suspend() and resume().

It uses a concept of permit and parking to detect if given thread should block or not. 

### park(), parkNanos(), and parkUntil() 

block/suspend the current thread until it is unparked by another thread with unpark( ), or until it is interrupted by another thread, or until the specified time elapses.

https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/locks/LockSupport.html

### problmes solved

1. bug of thread.suspend() and thread.resume()

2. compared with object.wait(), there is no need to acquire a lock first, and it won't throw interrupted exception.