

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

https://www.elastic.co/guide/en/elasticsearch/reference/current/tune-for-disk-usage.html

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
  - large cluster information makes the update operation slow
    - all updates need to be done through a single thread in order to guarantee consistency before the changes are distributed across the cluster.
 
## shard side too large or too small 
n Elasticsearch, each query is executed in a single thread per shard. Multiple shards can however be processed in parallel, as can multiple queries and aggregations against the same shard.

This means that the minimum query latency, when no caching is involved, will depend on the data, the type of query, as well as the size of the shard. Querying lots of small shards will make the processing per shard faster, but as many more tasks need to be queued up and processed in sequence, it is not necessarily going to be faster than querying a smaller number of larger shards. Having lots of small shards can also reduce the query throughput if there are multiple concurrent queries.

The best way to determine the maximum shard size from a query performance perspective is to benchmark using realistic data and queries. Always benchmark with a query and indexing load representative of what the node would need to handle in production, as optimizing for a single query might give misleading results.

## shrink or rollover the shard to a good size for you

https://www.elastic.co/blog/how-many-shards-should-i-have-in-my-elasticsearch-cluster

## design for scale

https://www.elastic.co/guide/en/elasticsearch/guide/2.x/scale.html

## replica number

If you have a cluster that has num_nodes nodes, num_primaries primary shards in total and if you want to be able to cope with max_failures node failures at once at most, then the right number of replicas is: 
```
replica number = max（max_failures，ceil（num_nodes /num_primaries） -  1）
```
## force merge segments of readonly replicas

Reduce segment number is good for search performance.

This should ideally be done once no more data is written to the index. Be aware that this is an expensive operation that should ideally be performed during off-peak hours.

by specifing `preference` in the search requests, the requests will go to the same node. 

```

GET /_search?preference=abcedf
{
    "query": {
        "match": {
            "title": "es"
        }
        }
}
```

# tunning search

https://www.elastic.co/guide/en/elasticsearch/reference/6.7/tune-for-search-speed.html

## fewer shards
searching over a lot of shards is quite expensive.

```
To solve the performance problems we investigated a recommendation that Elastic Support made to us early on: Reducing the number of shards. If you store time based events, be it news articles or log events, it is a common pattern to use date based indices. We started of with daily indices so that for example all news articles that have been published on the 29th of April 2018 would be stored in an index named articles-20180429. This means that, when you search over one year of data and you are using the default of 5 shards per index, Elasticsearch would have to search over 1825 shards. We learned that searching over a lot of shards is quite expensive. Indeed, up to some point, the cost for searching a fixed number of documents went up linearly with the number of shards involved. How to split up data across indices and shards most efficiently depends on many factors.

For our use case it made sense to make shards as big as possible. We reduced the number of shards per year from 1825 to 60 reducing query cost and latency on average by 90%.
```
## avoid leading wildcards or regex

## reference routing

the same requests may go to different nodes if you requests multiple times, this is not good for cache utilization.

## avoid join operation

- nested search is 10 times slower than normal search
- parent-child search 100 times slower than normal search.

## avoid range operation

## use keyword as long as you can

keywork is better than long integer for search

## use scroll instead of from&size

## norms, doc_values, \_source, field, score calculation

```
FieldData
线上查询出现偶尔超时的情况，通过调试查询语句，定位到是跟排序有关系。排序在es1.x版本使用的是FieldData结构，FieldData占用的是JVM Heap内存，
如果空间不足时，使用最久未使用（LRU）算法移除FieldData，同时加载新的FieldData Cache，加载的过程需要消耗系统资源，且耗时很大。所以导致这个查询的响应时间暴涨，甚至影响整个集群的性能。针对这种问题，解决方式是采用Doc Values。
Doc Values
Doc Values是一种列式的数据存储结构，跟FieldData很类似，但其存储位置是在Lucene文件中，即不会占用JVM Heap。随着ES版本的迭代，Doc Values比FieldData更加稳定，Doc Values在2.x起为默认设置。
```

# more to read

https://github.com/fdv/running-elasticsearch-fun-profit/blob/master/007-monitoring-es/007-monitoring-es.md

https://www.slideshare.net/fdevillamil/running-scaling-large-elasticsearch-clusters-81015284


# references

- [tunning for index speed](https://www.elastic.co/guide/en/elasticsearch/reference/current/tune-for-indexing-speed.html)
- [tunning for disk usage](https://www.elastic.co/guide/en/elasticsearch/reference/current/tune-for-disk-usage.html)
- [ES memory setup](https://www.elastic.co/guide/en/elasticsearch/reference/current/setup-configuration-memory.html)
- [How many shard should I have](https://www.elastic.co/blog/how-many-shards-should-i-have-in-my-elasticsearch-cluster)
- [the right replia number](https://www.elastic.co/guide/en/elasticsearch/reference/master/tune-for-search-speed.html)
- [fewer shards, more performance](
https://www.elastic.co/cn/blog/signal-media-optimizing-for-more-elasticsearch-power-with-less-elasticsearch-cluster)
