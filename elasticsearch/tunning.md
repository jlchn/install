# tune for index speed

## use bulk request

### how to know the optimal size of a bulk request
- run a benchmark on a single node with a single shard. 
- First try to index 100 documents at once, then 200,  etc. doubling the number of documents in the next runs.

### the adviced bulk size?

Be sure `indices.memory.index_buffer_size` is large enough(__at most__ 512 MB per shard, beyond that indexing performance does not typically improve) if there is heavy index request on this shard.
 
The default is 10% which is often plenty: for example, if you give the JVM 10GB of memory, it will give 1GB to the index buffer, which is enough to host two shards that are heavily indexing.


## use multiple threads to send bulk request

### how to know the optimal size of threads

- similar to sizing bulk request
- pay attention to TOO_MANY_REQUESTS (429) or EsRejectedExecutionException with the Java client

## index buffer size

## unset or increase the refresh interval

the `refresh` is used to make the new documents searchable.

by default, ES  periodically refreshes indices 1 second, increasing `index.refresh_interval` to a larger value will help inprove indexing speed, but in this case, it may take longer time for users to see the new documents.

by setting `index.refresh_interval` to -1 and `index.number_of_replicas` to 0, indexing will be faster since documents will be indexed only once. but this will temporarily put your index at risk since the loss of any shard will cause data loss, this is useful when you need to load a large amount of data at once.

## disable swapping

Operating systems will use as much memory as possible for file system caches and swap unused application memory to disk. 

This will make JVM heap or even its executable pages being swapped out to disk.

It may cause a long time(mibutes) GC instead of milliseconds and thus cause nodes to respond slowly or even to disconnect from the cluster.

### how to disable swapping
#### method 1
```
sudo swapoff -a # disable temporarily
#disable perminantely: comment out any lines that contain the word swap
vim /etc/fstab

```
#### method 2
set `vm.swappiness` t0 `1`

#### method 3

use mlockall to lock the process address space into RAM, preventing any ES memory from being swapped out.
```
vim config/elasticsearch.yml
bootstrap.memory_lock: true

```

## More memory for fs cache 

The filesystem cache will be used in order to buffer I/O operations. 

You should make sure to reserve at least half the instance memory for filesystem cache

## use auto-genereated id

When indexing a document that has an explicit id, Elasticsearch needs to check whether a document with the same id already exists within the same shard, which is a costly operation and gets even more costly as the index grows. 

By using auto-generated ids, Elasticsearch can skip this check, which makes indexing faster.

## faster hardware

SSD drives better than spinning disks

# tunning disk usage

##  use time-based indices

segments are immutable
 - updating a document requires Elasticsearch to first find the existing document, then mark it as deleted and add the updated version. 
 - eleting a document also requires the document to be found and marked as deleted. For this reason, deleted documents will continue to tie up disk space and some system resources until they are merged out, which can consume a lot of system resources.

Elasticsearch allows complete indices to be deleted very efficiently directly from the file system, without explicitly having to delete all records individually. This is by far the most efficient way to delete data from Elasticsearch.

## avoid large cluster state information

 It is important to find a good balance between the number of indices and shards, and the mapping size for each individual index
 
- [cluster state](https://www.elastic.co/guide/en/elasticsearch/guide/2.x/finite-scale.html#finite-scale)
  - stores mappings of indices
  - stores data structures holding information at the shard level
  - stores data structures holding information at the segment level(where data reside on disk)
  - stores cluster node information.

- the cluster state is loaded into memeory(the JVM heap) on every node 
  - it is important to manage heap usage and reduce the amount of cluster information as much as possible. The more heap space a node has, the more shards it can handle.
    - Small shards result in small segments, which increases more cluster inforamtion.
      - forcing smaller segments to merge into larger ones through a forcemerge operation can reduce overhead and improve query performance. This should ideally be done once no more data is written to the index. Be aware that this is an expensive operation that should ideally be performed during off-peak hours.
  - large cluster information makes the update operation slow
    - all updates need to be done through a single thread in order to guarantee consistency before the changes are distributed across the cluster.
  
# references

- [tunning for index speed](https://www.elastic.co/guide/en/elasticsearch/reference/current/tune-for-indexing-speed.html)
- [tunning for disk usage](https://www.elastic.co/guide/en/elasticsearch/reference/current/tune-for-disk-usage.html)
- [ES memory setup](https://www.elastic.co/guide/en/elasticsearch/reference/current/setup-configuration-memory.html)
-[How many shard should I have](https://www.elastic.co/blog/how-many-shards-should-i-have-in-my-elasticsearch-cluster)
