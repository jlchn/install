
### what is locksupport

LockSupport provides an alternative for some of Thread's deprecated methods: suspend() and resume().

It uses a concept of permit and parking to detect if given thread should block or not. 

### park(), parkNanos(), and parkUntil() 

block/suspend the current thread until it is unparked by another thread with unpark( ), or until it is interrupted by another thread, or until the specified time elapses.

https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/locks/LockSupport.html

### problmes solved

1. bug of thread.suspend() and thread.resume()

2. compared with object.wait(), there is no need to acquire a lock first, and it won't throw interrupted exception.


### examples

``` java

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("before park");
                LockSupport.park(this);
                System.out.println("after park");
            }
        });
        thread.start();
        System.out.println("before unpark");
        LockSupport.unpark(thread);
        System.out.println("after unpark");
```

in this example, we cannot tell the sequence of park() and unpark(), but by executing this codes, we will find the `thread` would always finish the work. 

this is because there is a `permit` status prepared for every thread.

if the current thread call park() and the `permit` is false, then it would block itself until the `permit` is set as true by another thread by calling `unpark(thread)`, or until it is interrupted by another thread, or until the specified time elapses. 


if currrent thread call park() and the `permit` is true, the it would set the `permit` as false and then return immediately without blocking itself. 