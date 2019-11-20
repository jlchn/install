# how to find the primary shard for write or read

```
shard = hash(routing) % number_of_primary_shards
```
the routing is the document id by default.

this is why we need to re-index after changing the `number_of_primary_shards` after index created

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
  

  
 # read
- the coordinating node resolves the read requests
- select an active copy of each relevant shard, from the shard replication group. This can be either the primary or a replica. By default, Elasticsearch will simply round robin between the shard copies.
- send shard level read requests to the selected copies.  
- combine the results and respond. in the case of get by ID look up, only one shard is relevant and this step can be skipped.
 
# segment merge

 merge many segment files to a larger one.
 
 ## what does segment merge do?
 
- create a new segment, this segment contains several existing old segments.
- open this segment to make it visible for searches.
- delete the old segments
- the documents marked as `deleted` will be deleted directly in this action.

 ## what do you need segment merge?
 
- each segment should be open for search, when there are too many segments, there would be more opeing files which may reach the opening-file-limit(if you didn't set it to unlimited)
- while searching a shard, ES will search all segments one by one(or with limited parallel). if there are too many segments, the search would be slow, especially when there are too many search actions queued.
- reduce the size of cluster state information.
- get more disk because the `deleted` documents will be physical deleted from disk.

## side effect of segment merge

- high IO while merging
