The fork/join is an implementation of a divide and conquer approach.

In practice, this means that the framework first “forks”, recursively breaking the task into smaller independent subtasks until they are simple enough to be executed asynchronously.

After that, the “join” part begins, in which results of all subtasks are recursively joined into a single result, or in the case of a task which returns void, the program simply waits until every subtask is executed.

fork/join framework supports the work stealing algorith which means by default, a worker thread gets tasks from the head of its own deque. When it is empty, the thread takes a task from the tail of the deque of another busy thread or from the global entry queue.

fork: put the sub-task to the queue

join: get the result of a sub-task.

``` java
public class ForkJoinMain {
    public static void main(String[] args) throws ExecutionException, InterruptedException {

        ForkJoinPool forkJoinPool = new ForkJoinPool(16);

        AddNumberTask addNumberTask = new AddNumberTask(0, 100000L);
        ForkJoinTask result = forkJoinPool.submit(addNumberTask);

        System.out.println(result.get());
    }
}

class AddNumberTask extends RecursiveTask<Long> {

    private static final int THRESHOLD = 1000;
    private long start;
    private long end;
    public AddNumberTask(long start, long end){
        this.start = start;
        this.end = end;
    }

    @Override
    protected Long compute() {
        long sum = 0;

        if (end - start < THRESHOLD){
            for (long i = start; i <= end; i++){
                sum = sum + i;
            }
        }else{
            List<AddNumberTask> subTasks = new ArrayList<>();
            long step = (end - start) / 100;
            long subStart = start;
            for (long i =0; i < 100; i++ ){
                long subEnd = subStart + step;
                if (subEnd > end){
                    subEnd = end;
                }
                AddNumberTask subTask = new AddNumberTask(subStart, subEnd);
                subTasks.add(subTask);
                subTask.fork(); // add to the fork join queue
                subStart = subEnd + 1;
            }

            for (AddNumberTask subTask : subTasks){
                sum = sum + subTask.join(); // get result
            }
        }

        return sum;
    }
}

```
