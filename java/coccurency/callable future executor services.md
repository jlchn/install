
Callable is similar to Runnable which allows us to define a thread, however, with Runnable we can only create a thread without returning value, we can do this with Callable.

### the defination of Callable

``` java
public interface Callable<V> {
    /**
     * Computes a result, or throws an exception if unable to do so.
     *
     * @return computed result
     * @throws Exception if unable to compute a result
     */
    V call() throws Exception;
}
```

### usage

the Callable is usually used with Future, FutureTask and ExecutorService. Below are some method definations in ExecutionService related to Callable and Future.

```java
<T> Future<T> submit(Callable<T> task);
Future<?> submit(Runnable task);
```

Blow is an example

``` java
public class LogSupportMain {

    public static void main(String[] args) throws InterruptedException, ExecutionException {


        ExecutorService executorService = Executors.newFixedThreadPool(1);
        Future<Integer> future1  = executorService.submit(new Task());
        Future<Integer> future2  = executorService.submit(new Task());

        while (!future1.isDone() && !future2.isDone()){
            System.out.println("calculating...");
            Thread.sleep(500);
        }

        Integer ret = future1.get() + future2.get();
        System.out.println(ret);

    }
}

class Task implements Callable<Integer>{
    @Override
    public Integer call() throws Exception {
        Thread.sleep(1000);
        int sum = 0;
        for(int i=0;i<100;i++)
             sum++;
        return sum;
    }
}
```
outout:
```
calculating...
calculating...
200
```

Future.isDone() tells us if the executor has finished the task. If the task is finished, it will return true otherwise, it returns false.

Future.get() returns the actual result. Notice that this method blocks the execution until the task is complete, but in our example, this won’t be an issue since we’ll check first if the task is completed by calling isDone().