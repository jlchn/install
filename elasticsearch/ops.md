### shards and replicas

https://stackoverflow.com/questions/15694724/shards-and-replicas-in-elasticsearch

https://www.elastic.co/guide/en/elasticsearch/reference/6.2/_basic_concepts.html

### Running a cluster without replicas
https://discuss.elastic.co/t/running-a-cluster-without-replicas/129846

### check status of the cluster
```
curl -XGET 'http://localhost:9200/_cluster/health?pretty'
{
  "cluster_name" : "es_cluster",
  "status" : "green",
  "timed_out" : false,
  "number_of_nodes" : 3,
  "number_of_data_nodes" : 3,
  "active_primary_shards" : 89,
  "active_shards" : 193,
  "relocating_shards" : 0,
  "initializing_shards" : 0,
  "unassigned_shards" : 0,
  "delayed_unassigned_shards" : 0,
  "number_of_pending_tasks" : 0,
  "number_of_in_flight_fetch" : 0,
  "task_max_waiting_in_queue_millis" : 0,
  "active_shards_percent_as_number" : 100.0
}

```

### list all indices

```
curl -XGET 'http://localhost:9200/_cat/indices?v' 

```

### list which node contains which shards

 below will tell the detailed view of what nodes contain which shards, and it will tell if it’s a primary or replica

```
curl -X GET "localhost:9200/_cat/shards?v"
...
curl -XGET 'http://localhost:9200/_cat/shards/index-name'
benchmark-test 2 p STARTED 439717 82.5mb 10.x.x.1 elasticsearch-0 
benchmark-test 2 r STARTED 439717 82.8mb 10.x.x.3 elasticsearch-2 
benchmark-test 4 r STARTED 439937 82.6mb 10.x.x.1 elasticsearch-0 
benchmark-test 4 p STARTED 439937 82.5mb 10.x.x.2 elasticsearch-1 
benchmark-test 3 p STARTED 438796 82.6mb 10.x.x.1 elasticsearch-0 
benchmark-test 3 r STARTED 438796 82.9mb 10.x.x.2 elasticsearch-1 
benchmark-test 1 r STARTED 439489 82.3mb 10.x.x.3 elasticsearch-2 
benchmark-test 1 p STARTED 439489 82.3mb 10.x.x.2 elasticsearch-1 
benchmark-test 0 p STARTED 440191 82.6mb 10.x.x.1 elasticsearch-0 
benchmark-test 0 r STARTED 440191 82.4mb 10.x.x.3 elasticsearch-2
```
