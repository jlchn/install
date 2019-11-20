# 429 too many requests

the error is due to overload of the queue capicity: Elasticsearch is queuing too many requests and cannot accept more.

this is usually happen while you are indexing too many documents via bulk API.

you can try to enlarge the queue size in elasticsearch.yml

```
thread_pool.bulk.queue_size: 500
```

be ware that making the queue too large require more memory to keep the requests.

check below links for more information.

https://www.elastic.co/guide/en/elasticsearch/reference/current/modules-threadpool.html

https://www.elastic.co/cn/blog/why-am-i-seeing-bulk-rejections-in-my-elasticsearch-cluster

https://www.elastic.co/cn/blog/performance-considerations-elasticsearch-indexing


# slow query checklist

- how big is the index, how many shards
- mapping design
    - number to keyword
    - use filter as long as you can
- returning value
    - only return the fields you use(do not use \_source)
    - return too many documments
- check cluster state: cpu, memory, load
- check the network
