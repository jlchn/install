# write

- request comes
  - the coordinating node find the primary shard according to `routing` rule
  - data stores in jvm indexing-buffer(10% of heap size by default), then acknowledge client the write was succeed.
    - the data is not visible to user searches yet.
  - the primary shard forward the requests to other replica, Once all replicas have successfully performed the operation and responded to the primary, the primary acknowledges the successful completion of the request to the client.
  
- refresh
  - periodly(default 1s) fetch data from jvm indexing-buffer, and store the data to filesystem cache(in memeory)
  - each refresh will result in a segment file(but still in the memory in this stage).
  - data here are visible to user searches.
  - all the index/delete/update operations are written to the translog and the translog is fsync’ed after every index/delete/update operation (or every 5 sec by default) to make sure the changes are persistent.
- flush((Lucene commit, fsync)
  - write segment files(in memory cache) to the disk(as disk segment file)
  - performed by default every 30 min or when the translog gets too big (default is 512MB).
  
- merge 
  - merge many segment files to a larger one.
  
 # read
- the coordinating node resolves the read requests
- select an active copy of each relevant shard, from the shard replication group. This can be either the primary or a replica. By default, Elasticsearch will simply round robin between the shard copies.
- send shard level read requests to the selected copies.  
- combine the results and respond. in the case of get by ID look up, only one shard is relevant and this step can be skipped.
 
