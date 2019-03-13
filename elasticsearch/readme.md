
### create an index 

```
curl -X PUT "localhost:9200/books" -H 'Content-Type: application/json' -d'
{
    "settings" : {
        "index" : {
            "number_of_shards" : 3,
            "number_of_replicas" : 2
        }
    }
}
'
```

### bulk insert documents to the index

```
curl -X PUT "localhost:9200/books/_doc/_bulk?pretty" -H 'Content-Type: application/json' -d'
{ "index": { "_id": 1 }}
    { "title": "Elasticsearch: The Definitive Guide", "authors": ["clinton gormley", "zachary tong"], "summary" : "A distibuted real-time search and analytics engine", "publish_date" : "2015-02-07", "num_reviews": 20, "publisher": "oreilly" }
    { "index": { "_id": 2 }}
    { "title": "Taming Text: How to Find, Organize, and Manipulate It", "authors": ["grant ingersoll", "thomas morton", "drew farris"], "summary" : "organize text using approaches such as full-text search, proper name recognition, clustering, tagging, information extraction, and summarization", "publish_date" : "2013-01-24", "num_reviews": 12, "publisher": "manning" }
    { "index": { "_id": 3 }}
    { "title": "Elasticsearch in Action", "authors": ["radu gheorge", "matthew lee hinman", "roy russo"], "summary" : "build scalable search applications using Elasticsearch without having to do complex low-level programming or understand advanced data science algorithms", "publish_date" : "2015-12-03", "num_reviews": 18, "publisher": "manning" }
    { "index": { "_id": 4 }}
    { "title": "Solr in Action", "authors": ["trey grainger", "timothy potter"], "summary" : "Comprehensive guide to implementing a scalable search engine using Apache Solr", "publish_date" : "2014-04-05", "num_reviews": 23, "publisher": "manning" }
'
```

### full-text search(match): search on all fields

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "multi_match" : {
            "query" : "guide" 
        }
    }
}
```

### search on specific fileds
```
 curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "multi_match" : {
            "query" : "guide",
            "fields" : ["title", "authors", "summary"]
        }
    }
}
'
```

### return specific fields and number of results

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
        "query": {
                "match": {
                        "title": "in action"
                }
        },
        "size": 1,
        "from": 0,
        "_source": ["title"]
}'
{
  "took" : 2,
  "timed_out" : false,
  "_shards" : {
    "total" : 3,
    "successful" : 3,
    "skipped" : 0,
    "failed" : 0
  },
  "hits" : {
    "total" : 2,
    "max_score" : 1.7427701,
    "hits" : [
      {
        "_index" : "books",
        "_type" : "_doc",
        "_id" : "4",
        "_score" : 1.7427701,
        "_source" : {
          "title" : "Solr in Action"
        }
      }
    ]
  }
}

```
### increase the importance of the some field

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
        "query": {
                "multi_match": {
                        "query": "guide", "fields":["title","summary^3"]
                }
        },
        "_source": ["title","summary"]        
}'
```

### bool query
The AND/OR/NOT operators can be used to fine tune our search queries in order to provide more relevant or specific results. This is implemented in the search API as a bool query. The bool query accepts a must parameter (equivalent to AND), a must_not parameter (equivalent to NOT), and a should parameter (equivalent to OR). For example, if I want to search for a book with the word “Elasticsearch” OR “Solr” in the title, AND is authored by “clinton gormley” but NOT authored by “radu gheorge”

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
"query": {
    "bool": {
      "must": {
        "bool" : {
          "should": [
            { "match": { "title": "Elasticsearch" }},
            { "match": { "title": "Solr" }}
          ],
          "must": { "match": { "authors": "clinton gormely" }}
        }
      },
      "must_not": { "match": {"authors": "radu gheorge" }}
    }
  }
}'

```
 a bool query can wrap any other query type including other bool queries to create arbitrarily complex or deeply nested queries

### fuzzy query

Fuzzy matching can be enabled on Match and Multi-Match queries to catch spelling errors

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
"query": {
        "multi_match" : {                   
            "query" : "comprihensiv guide",
            "fields": ["title", "summary"],
            "fuzziness": "AUTO"
        }
    },
    "_source": ["title", "summary", "publish_date"],
    "size": 1
}'
```

Instead of specifying "AUTO" you can specify the numbers 0, 1, or 2 to indicate the maximum number of edits that can be made to the string to find a match. The benefit of using "AUTO" is that it takes into account the length of the string. For strings that are only 3 characters long, allowing a fuzziness of 2 will result in poor search performance. Therefore it's recommended to stick to "AUTO" in most cases.

### wildcard query
 Wildcard queries allow you to specify a pattern to match instead of the entire term. ? matches any character and * matches zero or more characters.

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
"query": {
           "wildcard":{"authors":"t*"}
         },
    "_source": ["authors"] 
}'

```

### regexp query

```

curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
"query": {
           "regexp":{"authors":"t[a-z]*y"}
         },
    "_source": ["authors"]
}'

```


### match phrase query

The match phrase query requires that all the terms in the query string be present in the document, be in the order specified in the query string and be close to each other. 

By default, the terms are required to be exactly beside each other but you can specify the slop value which indicates how far apart terms are allowed to be while still considering the document a match.

```
 curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "multi_match" : {
            "query" : "search engine",
	    "type" : "phrase",
            "slop" : 3,
            "fields" : ["title", "authors", "summary"]
        }
    }
}
'
```

### term query

The term query finds documents that contain the exact term in the inverted index.

```

 curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        
            "term" : {"title":"action"}
    }
}
'
```

it doesn’t know anything about the field’s analyzer. This makes it useful for looking up values in keyword fields, or in numeric or date fields. When querying full text fields, use the match query instead, which understands how the field has been analyzed.

```
PUT my_index
{
  "mappings": {
    "_doc": {
      "properties": {
        "full_text": {
          "type":  "text" 
        },
        "exact_value": {
          "type":  "keyword" 
        }
      }
    }
  }
}

PUT my_index/_doc/1
{
  "full_text":   "Quick Foxes!", 
  "exact_value": "Quick Foxes!"  
}

GET my_index/_search
{
  "query": {
    "term": {
      "exact_value": "Quick Foxes!" 
    }
  }
}

GET my_index/_search
{
  "query": {
    "term": {
      "full_text": "Quick Foxes!" 
    }
  }
}

GET my_index/_search
{
  "query": {
    "term": {
      "full_text": "foxes" 
    }
  }
}

GET my_index/_search
{
  "query": {
    "match": {
      "full_text": "Quick Foxes!" 
    }
  }
}

```

First query matches because the exact_value field contains the exact term Quick Foxes!.

The second query does not match, because the full_text field only contains the terms quick and foxes. It does not contain the exact term Quick Foxes!.

The third term query for the term foxes matches the full_text field.

The fourth query is a match query, this match query on the full_text field first analyzes the query string, then looks for documents containing quick or foxes or both


### References

https://www.elastic.co/guide/en/elasticsearch/reference/current/query-dsl-term-query.html

https://dzone.com/articles/23-useful-elasticsearch-example-queries


