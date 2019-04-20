### create an instance of Unsafe

We can use the static method getUnsafe().

``` java
 public static Unsafe getUnsafe(){
        return Unsafe.getUnsafe();
    }
```

 But by default, this will throw a SecurityException. If we see the implementation of get `getUnsafe()`, there is a security check there.

 ```java
public static Unsafe getUnsafe() {
    Class cc = sun.reflect.Reflection.getCallerClass(2);
    if (cc.getClassLoader() != null)
        throw new SecurityException("Unsafe");
    return theUnsafe;
}
 ```

The other way is to create using reflection

``` java
Field f = Unsafe.class.getDeclaredField("theUnsafe");
f.setAccessible(true);
unsafe = (Unsafe) f.get(null);
```

### instantiate a Class Using Unsafe to avoid initialization

`allocateInstance` method can be useful when you need to skip object initialization phase or bypass security checks in constructor or you want instance of that class but don’t have any public constructor. 

``` java

class Obj {
    private int v;

    public Obj() {
        this.v = 1; // initialization
    }

    public long getV() { return this.v; }
}

 Obj obj1 = (Obj) unsafe.allocateInstance(Obj.class);
 Obj obj2 = new Obj();
 System.out.println(obj1.getV()); // 0
 System.out.println(obj2.getV()); // 1
```

### corrupt object field for security bypass

``` java
class Obj {
    private int v;

    public Obj() {
        this.v = 1; // initialization
    }

    public long getV() { return this.v; }
}

 Obj obj = new Obj();
 Field f = obj.getClass().getDeclaredField("v");
 unsafe.putInt(obj, unsafe.objectFieldOffset(f), 100);
 System.out.println(obj.getV()); // 100

```

### compare and swap operation

`Unsafe.compareAndSwap` methods are `atomic`  implement `lock-free` data structures.

``` java

public interface Counter {
    void increment();
    long get();
}

public class BadCounter implements Counter{

    private long count = 0;

    @Override
    public void increment() {
        count++;
    }

    @Override
    public long get() {
        return count;
    }
}

public class SynchronizedCounter implements Counter{

    private long count = 0;

    @Override
    public synchronized void increment() {
        count++;
    }

    @Override
    public long get() {
        return count;
    }
}

public class AtomicCounter implements Counter{

    private AtomicLong count = new AtomicLong(0);

    @Override
    public void increment() {
        count.incrementAndGet();
    }

    @Override
    public long get() {
        return count.get();
    }
}

public class PrimitiveUnsafeSupportCounter implements Counter{

    private volatile long count = 0; // 1
    private Unsafe unsafe;
    private long offset;

    public PrimitiveUnsafeSupportCounter() throws IllegalAccessException, NoSuchFieldException {
        Field f = Unsafe.class.getDeclaredField("theUnsafe");
        f.setAccessible(true);
        this.unsafe = (Unsafe) f.get(null);
        this.offset = this.unsafe.objectFieldOffset(PrimitiveUnsafeSupportCounter.class.getDeclaredField("count"));
    }

    @Override
    public void increment() {

//       long before;
//        do {
//            before = this.unsafe.getLongVolatile(this, this.offset);
//        } while (!this.unsafe.compareAndSwapLong(this, this.offset, before, before + 1));

        this.unsafe.getAndAddLong(this, this.offset, 1);// why this is faster than the above codes???
    }

    @Override
    public long get() {
        return this.count;
    }
}


public class CounterThread implements Runnable {

    private Counter counter;

    public CounterThread(Counter counter){
        this.counter = counter;
    }
    @Override
    public void run() {

        for (int i = 0; i < 100000; i ++){
            this.counter.increment();
        }
    }
}

class Test{

    public static void test(Counter counter) throws NoSuchFieldException, IllegalAccessException, InterruptedException {

        ExecutorService executor = Executors.newFixedThreadPool(1000);

        long start = System.currentTimeMillis();
        for (int i = 0 ; i < 1000; i++){
            executor.submit(new CounterThread(counter));
        }

        /**
         * The shutdown() method doesn’t cause an immediate destruction of the ExecutorService.
         * It will make the ExecutorService stop accepting new tasks and shut down after all
         * running threads finish their current work.
         */
        executor.shutdown();
        /**
         * Blocks until all tasks have completed execution after a shutdown
         * request, or the timeout occurs, or the current thread is interrupted
         */
        executor.awaitTermination(1, TimeUnit.MINUTES);
        long stop = System.currentTimeMillis();

        System.out.println(counter.get());
        System.out.println(stop - start);
    }

}

public class Main {
    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException, InterruptedException {



        Counter badCounter = new BadCounter();
        Test.test(badCounter);
        Counter synchronizedCounter = new SynchronizedCounter();
        Test.test(synchronizedCounter);
        Counter atomicCounter = new AtomicCounter();
        Test.test(atomicCounter);
        Counter primitiveUnsafeSupportCounter = new PrimitiveUnsafeSupportCounter();
        Test.test(primitiveUnsafeSupportCounter);

    }

}


```

output:

```
99636883
302
100000000
3571
100000000
2396
100000000
3129
```

### park and unpark

todo



