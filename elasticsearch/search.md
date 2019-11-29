# todo

- search from multiple indices.
-  score calculation


# Document CURD

## basic curd

```
# create a document with a auto-generated id
POST users/_doc
{
	"user" : "Mike",
    "post_date" : "2019-04-15T14:12:12",
    "message" : "trying out Kibana"
}

# create a document with a specified id, if there the id is already exist, an error would throw
PUT users/_doc/1?op_type=create
{
	"user" : "Jack",
    "post_date" : "2019-04-15T14:12:12",
    "message" : "trying out elasticsearch"
}

# create a document with a specified id, if there the id is already exist, an error would throw
PUT users/_create/1
{
	"user" : "Jack",
    "post_date" : "2019-04-15T14:12:12",
    "message" : "trying out elasticsearch"
}

GET users/_doc/1


# update a document, es will first delete the existing doc, then create the new doc, the version of new document increases by 1.
PUT users/_doc/1
{
	"user" : "Jack",
    "post_date" : "2019-04-15T14:12:12",
    "message" : "trying out elasticsearch"
}

# add new fields to existing documents or update the existing fields, the version of new document increases by 1.
POST users/_update/1
{
    "doc":{
        "release_date" : "2019-05-15T14:12:12",
        "message" : "new message"
    }
}

DELETE users/_doc/1

```

## bulk insert documents to the index

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

## bulk get

```
GET /_mget
{
    "docs" : [
        {
            "_index" : "users",
            "_id" : "1"
        },
        {
            "_index" : "users-2",
            "_id" : "2"
        }
    ]
}

GET /users/_mget
{
    "docs" : [
        {

            "_id" : "1"
        },
        {

            "_id" : "2"
        }
    ]
}

```



# Search 

- full-text search
    - search on one filed
    - search on all fields
    - search on specific/multiple fields
    - fuzzy search
    - search using wildcard
    - search using regex
    - match phrase search
    - match phrase prefix search
    - bool query
    - query string search
    - simple query string search
- structured/term search
    - single term search
    - multiple term search
    - sorted term search
    - ranged term search
- filter context vs query context
- limit result
    - limit return fileds
    - limit return documents
- boosting/optimizing filed score
    - add boosting number
    - function score
    - function scoring script

## full-text search


### search on one field

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "match" : {
            "title" : "guide" 
        }
    }
}
```
below will get the documents with fileds containing `final` or `guide` or `final and guide`

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "match" : {
            "title" : "final guide" 
        }
    }
}
```

below will get the documents with fileds must contain `final` and `guide`

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "match" : {
            "title" : {
	    	"query":"final guide",
		"operator":"AND"
	    } 
        }
    }
}


### search multiple words

```
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
    "query": {
        "multi_match" : {
            "query" : "final guide" 
        }
    }
}
```

### search on multiple/specific fileds

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


### fuzzy query

Fuzzy matching can be enabled on Match and Multi-Match queries to catch spelling errors

```bash
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

 Wildcard queries allow you to specify a pattern to match instead of the entire term. 
 - ? matches any character
 - * matches zero or more characters.

```bash
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
"query": {
           "wildcard":{"authors":"t*"}
         },
    "_source": ["authors"] 
}'

```

### regexp query

```bash

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

[Results]
"hits": [
      {
        "_index": "bookdb_index",
        "_type": "book",
        "_id": "4",
        "_score": 0.22327082,
        "_source": {
          "summary": "Comprehensive guide to implementing a scalable search engine using Apache Solr",
          "title": "Solr in Action",
          "publish_date": "2014-04-05"
        }
      },
      {
        "_index": "bookdb_index",
        "_type": "book",
        "_id": "1",
        "_score": 0.16113183,
        "_source": {
          "summary": "A distibuted real-time search and analytics engine",
          "title": "Elasticsearch: The Definitive Guide",
          "publish_date": "2015-02-07"
        }
      }
    ]
    
```

### match phrase prefix search
 
 for autocomplete feature
 
```
POST /bookdb_index/book/_search
{
    "query": {
        "match_phrase_prefix" : {
            "summary": {
                "query": "search en",
                "slop": 3,
                "max_expansions": 10
            }
        }
    },
    "_source": [ "title", "summary", "publish_date" ]
}
[Results]
"hits": [
      {
        "_index": "bookdb_index",
        "_type": "book",
        "_id": "4",
        "_score": 0.5161346,
        "_source": {
          "summary": "Comprehensive guide to implementing a scalable search engine using Apache Solr",
          "title": "Solr in Action",
          "publish_date": "2014-04-05"
        }
      },
      {
        "_index": "bookdb_index",
        "_type": "book",
        "_id": "1",
        "_score": 0.37248808,
        "_source": {
          "summary": "A distibuted real-time search and analytics engine",
          "title": "Elasticsearch: The Definitive Guide",
          "publish_date": "2015-02-07"
        }
      }
    ]
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



### query string

The query_string query provides a means of executing multi_match queries, bool queries, boosting, fuzzy matching, wildcards, regexp, and range queries in a concise shorthand syntax. In the following example, we execute a fuzzy search for the terms “search algorithm” in which one of the book authors is “grant ingersoll” or “tom morton.” We search all fields but apply a boost of 2 to the summary field.

```bash
POST /bookdb_index/book/_search
{
    "query": {
        "query_string" : {
            "query": "(saerch~1 algorithm~1) AND (grant ingersoll)  OR (tom morton)",
            "fields": ["title", "authors" , "summary^2"]
        }
    },
    "_source": [ "title", "summary", "authors" ],
    "highlight": {
        "fields" : {
            "summary" : {}
        }
    }
}
[Results]
"hits": [
  {
    "_index": "bookdb_index",
    "_type": "book",
    "_id": "2",
    "_score": 3.571021,
    "_source": {
      "summary": "organize text using approaches such as full-text search, proper name recognition, clustering, tagging, information extraction, and summarization",
      "title": "Taming Text: How to Find, Organize, and Manipulate It",
      "authors": [
        "grant ingersoll",
        "thomas morton",
        "drew farris"
      ]
    },
    "highlight": {
      "summary": [
        "organize text using approaches such as full-text <em>search</em>, proper name recognition, clustering, tagging"
      ]
    }
  }
]

```

### simple query string

The simple_query_string query is a version of the query_string query that is more suitable for use in a single search box that is exposed to users because it replaces the use of AND/OR/NOT with +/|/-, respectively, and it discards invalid parts of a query instead of throwing an exception if a user makes a mistake.

```bash
POST /bookdb_index/book/_search
{
    "query": {
        "simple_query_string" : {
            "query": "(saerch~1 algorithm~1) + (grant ingersoll)  | (tom morton)",
            "fields": ["title", "authors" , "summary^2"]
        }
    },
    "_source": [ "title", "summary", "authors" ],
    "highlight": {
        "fields" : {
            "summary" : {}
        }
    }
}

```

## term query

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

The third term query for the term foxes matches the full_text field. but be sure to [Avoid using the term query for text fields](https://www.elastic.co/guide/en/elasticsearch/reference/current/query-dsl-term-query.html)

The fourth query is a match query, this match query on the full_text field first analyzes the query string, then looks for documents containing quick or foxes or both


### mulitple terms

```
{
    "query": {
        "terms" : {
            "publisher": ["oreilly", "packt"]
        }
    }
}
```

### sorted term search 

```

POST /bookdb_index/book/_search
{
    "query": {
        "term" : {
            "publisher": "manning"
        }
    },
    "_source" : ["title","publish_date","publisher"],
    "sort": [
        { "publish_date": {"order":"desc"}}
    ]
}
```

### ranged term search

```
POST /bookdb_index/book/_search
{
    "query": {
        "range" : {
            "publish_date": {
                "gte": "2015-01-01",
                "lte": "2015-12-31"
            }
        }
    },
    "_source" : ["title","publish_date","publisher"]
}

```

## filter context vs query context

- query context
    - how well does this document match this query clause?
    - the query clause also calculates a relevance score in the _score_ filed
- filter context
    - Does this document match this query clause?
    - the answer is a simple `Yes` or `No` — no scores are calculated
    - filter context is mostly used for filtering structured data(term search)
        - Does this timestamp fall into the range 2015 to 2016?
	- Is the status field set to "published"?
    - filter context takes effects in
        - `filter` or `must_not` parameters in the `bool` query
	- the `filter` parameter in the `constant_score` query
	- the `filter` aggregation


__Use filter context instead of query context if possible.__

```
curl -X GET "localhost:9200/_search?pretty" -H 'Content-Type: application/json' -d'
{
  "query": {  //1
    "bool": { //2
      "must": [
        { "match": { "title":   "Search"        }},
        { "match": { "content": "Elasticsearch" }}
      ],
      "filter": [ //3
        { "term":  { "status": "published" }},
        { "range": { "publish_date": { "gte": "2015-01-01" }}}
      ]
    }
  }
}
'

```

- The `query` parameter indicates query context
- The `bool` and two `match` clauses are used in query context, which means that they are used to score how well each document matches.
- The filter parameter indicates filter context, they will not affect the score for matching documents.

## limit results

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

[result:]
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

## boosting/optimizing filed score

while searching across multiple fields, we may want to highlight the importance of a certain field. 


### increase the importance of an field by adding boosting number

search without boosting number

```bash
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
        "query": {
                "multi_match": {
                        "query": "guide", "fields":["title","summary"]
                }
        },
        "_source": ["title","summary"]        
}'
```

search with boosting number on field `title` 
```bash
curl -X GET "localhost:9200/books/_search?pretty" -H 'Content-Type: application/json' -d '{
        "query": {
                "multi_match": {
                        "query": "guide", "fields":["title","summary^3"]
                }
        },
        "_source": ["title","summary"]        
}'
```

### function score

Suppose that instead of wanting to boost incrementally by the value of a field, you have an ideal value you want to target and you want the boost factor to decay the further away you move from the value. This is typically useful in boosts based on lat/long, numeric fields like price, or dates. In our contrived example, we are searching for books on “search engines” ideally published around June 2014.

```
POST /bookdb_index/book/_search
{
    "query": {
        "function_score": {
            "query": {
                "multi_match" : {
                    "query" : "search engine",
                    "fields": ["title", "summary"]
                }
            },
            "functions": [
                {
                    "exp": {
                        "publish_date" : {
                            "origin": "2014-06-15",
                            "offset": "7d",
                            "scale" : "30d"
                        }
                    }
                }
            ],
            "boost_mode" : "replace"
        }
    },
    "_source": ["title", "summary", "publish_date", "num_reviews"]
}
```
### function score: script scoring

we want to specify a script that takes into consideration the publish_date before deciding how much to factor in the number of reviews. Newer books may not have as many reviews yet so they should not be penalized for that.

scoring script:
```groovy

publish_date = doc['publish_date'].value
num_reviews = doc['num_reviews'].value
if (publish_date > Date.parse('yyyy-MM-dd', threshold).getTime()) {
  my_score = Math.log(2.5 + num_reviews)
} else {
  my_score = Math.log(1 + num_reviews)
}
return my_score
```
search dsl
```bash

POST /bookdb_index/book/_search
{
    "query": {
        "function_score": {
            "query": {
                "multi_match" : {
                    "query" : "search engine",
                    "fields": ["title", "summary"]
                }
            },
            "functions": [
                {
                    "script_score": {
                        "params" : {
                            "threshold": "2015-07-30"
                        },
                        "script": "publish_date = doc['publish_date'].value; num_reviews = doc['num_reviews'].value; if (publish_date > Date.parse('yyyy-MM-dd', threshold).getTime()) { return log(2.5 + num_reviews) }; return log(1 + num_reviews);"
                    }
                }
            ]
        }
    },
    "_source": ["title", "summary", "publish_date", "num_reviews"]
}

```
# explain

```
GET /tmdb/_validate/query?explain
{
  "query": {
        "multi_match" : {                   
            "query" : "alien Resurrection",
            "fields": ["title^10", "overview"]
            
        }
    }
}

[output]
{
  "_shards" : {
    "total" : 1,
    "successful" : 1,
    "failed" : 0
  },
  "valid" : true,
  "explanations" : [
    {
      "index" : "tmdb",
      "valid" : true,
      "explanation" : "((overview:alien overview:resurrect) | (title:alien title:resurrect)^10.0)"
    }
  ]
}

```
# References

https://www.elastic.co/guide/en/elasticsearch/reference/current/query-dsl-term-query.html

https://dzone.com/articles/23-useful-elasticsearch-example-queries

https://www.elastic.co/guide/en/elasticsearch/reference/current/query-filter-context.html
