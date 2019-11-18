# index API
## get all indices

```
GET /_cat/indices?v&s=docs.count:desc # sort by docs.count
health status index                           uuid                   pri rep docs.count docs.deleted store.size pri.store.size
green  open   kibana_sample_data_logs         v1I7erYcRHujiK5CVQxXpg   1   1      14074            0     22.5mb         11.1mb
green  open   kibana_sample_data_flights      WzIlfHD2TjuyO30t2RXjAA   1   1      13059            0     12.6mb          6.3mb
green  open   movies                          nosuhiglRyy5Vlj826tuOw   1   1       9743            0      2.7mb          1.4mb
green  open   kibana_sample_data_ecommerce    tOwf7US-TaWrI2CzW4dRVg   1   1       4675            0      9.3mb          4.5mb
green  open   .kibana_1                       vbhxx1ZDRoqGZ9siAY46PA   1   1        167            9        2mb            1mb
green  open   .monitoring-es-7-2019.11.15     X0ZRgi-0RZCozPaAm29Xow   1   1         93           36        5mb          2.3mb
green  open   .monitoring-kibana-7-2019.11.15 MzcD29ghTRCORqEdUbWPMA   1   1          3            0    316.1kb        109.5kb
green  open   .kibana_task_manager_1          EidAbBTxQZ6rMfb3VUnHkQ   1   1          2            0     25.1kb         12.5kb
green  open   .apm-agent-configuration        6WuZNNGoR_-UrOR33nwDiA   1   1          0            0       566b           283b

GET /_cat/indices/kibana*?v&s=docs.count:desc

health status index                        uuid                   pri rep docs.count docs.deleted store.size pri.store.size
green  open   kibana_sample_data_logs      v1I7erYcRHujiK5CVQxXpg   1   1      14074            0     22.5mb         11.1mb
green  open   kibana_sample_data_flights   WzIlfHD2TjuyO30t2RXjAA   1   1      13059            0     12.6mb          6.3mb
green  open   kibana_sample_data_ecommerce tOwf7US-TaWrI2CzW4dRVg   1   1       4675            0      9.3mb          4.5mb


```

reference: https://www.elastic.co/guide/en/elasticsearch/reference/current/cat-indices.html

## create an index 

```
curl -X PUT "localhost:9200/movies" -H 'Content-Type: application/json' -d'
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
## check the settings and mappings of an index

```
GET movies

{
  "movies" : {
    "aliases" : { },
    "mappings" : {
      "properties" : {
        "@version" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        },
        "genre" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        },
        "id" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        },
        "title" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        },
        "year" : {
          "type" : "long"
        }
      }
    },
    "settings" : {
      "index" : {
        "creation_date" : "1573805733948",
        "number_of_shards" : "1",
        "number_of_replicas" : "1",
        "uuid" : "nosuhiglRyy5Vlj826tuOw",
        "version" : {
          "created" : "7040299"
        },
        "provided_name" : "movies"
      }
    }
  }
}

```

## check the doc count of an index

```bash
GET movies/_count
```

# index concept

## removal of index types

before 7.0, an index can be defined with many kind of Types,

after 7.0, type can only be `_doc`, see https://www.elastic.co/guide/en/elasticsearch/reference/6.0/removal-of-types.html for more information


## the reverse index

the reverse index consists of a term dictionary and a posting list(倒排列表)
- term dictionary
    - B+ tree or HashMap to keep the term
- posting list
    - doc id: which documents include this term, 
    - term frequency: how many times does this term appear in each documents, this is useful for search score calculating.
    - term position: the positions the term in the document, this is useful for phrase query.
    - offset: the start and end of this term, this is useful for highlight the term in the search result.

let's say we have 3 documents:
```
Document 1: hello world
Document 2: hello java
Document 3: hello Elasticsearch
```

the structure of reverse index seems like below: 

| Term        | Count           | DocumentId:Position in the Document:offset  |
| ------------- |:-------------:| -----:|
| hello      | 3 | 1:1:<0,4>,2:1:<0,4>,3:1:<0,4> |
| java     | 1      |   2:2:<6,9> |
| elasticsearch | 1      | 3:2:<6:17> |
    
### the reverse index in Elasticsearch

- each field in an Elasticsearch document has a reverse index.
- the fields can be set not to have an index.
    - the fields can't be searched in this case.
    - help you save the storage.
 
## the analyzer

the analyzer is used to split the whole document to terms/tokens.

```
+-----------------------------------------------------------------------------------------------------------------------+
|                                                                                                                       |
| Analyzer                                                                                                              |
|                                                                                                                       |
|    +------------------------+                +--------------------------+          +----------------------------+     |
|    |                        |   document     |                          |  terms   |                            |     |
|    | Character Filters      +---------------->  Tokenizer               +--------->+  Token Filter              |     |
|    |                        |                |                          |          |                            |     |
|    +------------------------+                +--------------------------+          +----------------------------+     |
|     remove html                               split document to terms               remove stop words(the, a, is)     |
|                                                                                     add synonym term                  |
|                                                                                     to upper/lower case               |
|                                                                                                                       |
+-----------------------------------------------------------------------------------------------------------------------+

```

- Character Filters
    - A character filter receives the original text as a stream of characters and can transform the stream by adding, removing, or changing characters
    - An analyzer may have zero or more character filters, which are applied in order.
        - HTML Strip Character Filter: remove html elements
        - Mapping Character Filter: replace by key-value pairs
        - Pattern Replace Character Filter: replace by regex pattern
- Tokenizer
    - A tokenizer receives a stream of characters, breaks it up into individual tokens
    - Workd oriented tokenizers
        - Standard Tokenizer
            - it breaks the documents into terms on word boundaries(Unicode Text Segmentation algorithm)
            - It removes most punctuation symbols
        - Letter Tokenizer
            - The letter tokenizer divides text into terms whenever it encounters a character which is not a letter.
        - Lowercase Tokenizer
            - he lowercase tokenizer, like the letter tokenizer, divides text into terms whenever it encounters a character which is not a letter, but it also lowercases all terms.
        - Whitespace Tokenizer
            - The whitespace tokenizer divides text into terms whenever it encounters any whitespace character.
        - UAX URL Email Tokenizer
            -  it is like the standard tokenizer except that it recognises URLs and email addresses as single tokens
        - Classic Tokenizer
            - it is good only for English language documents.
            - It splits words at most punctuation characters, removing punctuation. However, a dot that’s not followed by whitespace is considered part of a token.
            - It splits words at hyphens, unless there’s a number in the token, in which case the whole token is interpreted as a product number and is not split.
            - It recognizes email addresses and internet hostnames as one token.
    - Partial word tokenizers
        - These tokenizers break up text or words into small fragments, for partial word matching
        - N-Gram Tokenizer
            - The ngram tokenizer can break up text into words when it encounters any of a list of specified characters (e.g. whitespace or punctuation), then it returns n-grams of each word: a sliding window of continuous letters, e.g. quick → [qu, ui, ic, ck].
        - Edge N-Gram Tokenizer
            - The edge_ngram tokenizer can break up text into words when it encounters any of a list of specified characters (e.g. whitespace or punctuation), then it returns n-grams of each word which are anchored to the start of the word, e.g. quick → [q, qu, qui, quic, quick]
    - Structured Text Tokenizers
        - Keyword Tokenizer
            - it dose nothing on the input.
        - Pattern Tokenizer
            - The pattern tokenizer uses a regular expression to either split text into terms whenever it matches a word separator, or to capture matching text as terms.
        - Simple Pattern Tokenizer
            - The simple_pattern tokenizer uses a regular expression to capture matching text as terms. 
        - Simple Pattern Split Tokenizer
            - The simple_pattern_split tokenizer uses the same restricted regular expression subset as the simple_pattern tokenizer, but splits the input at matches rather than returning the matches as terms.
        - Path Tokenizer
            - splits on the path separator, and emits a term for each component in the tree, e.g. /foo/bar/baz → [/foo, /foo/bar, /foo/bar/baz ].
- Token Filter
    - it can modify tokens (eg lowercasing), delete tokens (eg remove stopwords) or add tokens (eg synonyms).
    
- Token Filter
the build-in analyzers in Elasticsearch

| analyzer                  |  Character Filters            | Tokenizer             | Token Filter    |
| ------------------------- |:-----------------------------:| ---------------------:|----------------:|
| standard analyzer(defalut)| HTML Strip Character Filter   | Standard Tokenizer    | lowercase filter|
| stop analyzer             | HTML Strip Character Filter   | Lowercase Tokenizer   | stop filter     |
| simple analyzer           | HTML Strip Character Filter   | Lowercase Tokenizer   | none            |
| whiltespace analyzer      | none                          | whiltespace Tokenizer | none            |
| keyword analyzer          | none                          | keyword Tokenizer     | none            |
| pattern analyzer(default:\W )| HTML Strip Character Filter| pattern Tokenizer     | lowercase filter, stop filer|
- for the keyword analyzer, the analyzer do nothing, the entire input will be seen as the output.
- users can use custom analyzer.

### analyzer API


### characture filter

```bash

GET /_analyze
{
    "char_filter": ["html_strip"], 
    "tokenizer": "keyword",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

=> He's mother said: "THIS-is a No.1 主意."

GET /_analyze
{
    "char_filter": [
      {
      "type": "mapping", 
      "mappings": ["mother => father"]
      }
    ], 
    "tokenizer": "keyword",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

=> "<p>He's father said: "THIS-is a <b>No.1</b> 主意."</p>


```

### tokenizer


```
GET /_analyze
{
    "tokenizer": "whitespace",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

# html elements shown because no char_filter is specified
=> [<p>He's, mother, said:, "THIS-is, a, <b>No.1</b>, 主意.\"</p>]

```

### token filters

```
GET /_analyze
{
    "tokenizer": "whitespace",
    "filter": ["stop", "lowercase"],
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

=> [<p>he's, mother, said:, "this-is, <b>No.1</b>, 主意.\"</p>]
```


### analyzer 
```
GET /_analyze
{
    "analyzer": "standard",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

[p, he's, mother, said, this, is, a, b, no, 1, b, 主, 意, p]

GET /_analyze
{
    "analyzer": "simple",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

[p, he, s, mother, said, this, is, a, b, no, b, 主意, p]

GET /_analyze
{
    "analyzer": "whitespace",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}


[<p>He's, mother, said:, "THIS-is, a, <b>No.1</b>, 主意."</p>]


GET /_analyze
{
    "analyzer": "stop",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

[p, he, s, mother, said, b, b, 主意, p]

GET /_analyze
{
    "analyzer": "keyword",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

<p>He's mother said: "THIS-is a <b>No.1</b> 主意."</p>

GET /_analyze
{
    "analyzer": "pattern",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

[p, he, s, mother, said, this, is, a, b, no, 1, b, p]
```
### language analyzer

```
GET /_analyze
{
    "analyzer": "english",
    "text": "<p>He's mother said: \"THIS-is a <b>No.1</b> 主意.\"</p>"
}

GET /_analyze
{
    "analyzer": "icu_analyzer",
    "text": "<p>这个苹果挺好吃的\"</p>"
}
[这个, 苹果, 挺好, 吃, 的]


GET /_analyze
{
    "analyzer": "ik_max_word",
    "text": "<p>这个苹果挺好吃的\"</p>"
}

[p 这个, 苹果, 挺好吃, 好吃, 好吃, 的, p]
```

### costimize an analyzer

```bash 
PUT /my_index
{
    "settings":{
        "analysis":{
            "char_filter":{
                "&_to_and":{
                    "type":"mapping",
                    "mappings":[
                        "&=> and "
                    ]
                }
            },
            "filter":{
                "my_stopwords":{
                    "type":"stop",
                    "stopwords":[
                        "the",
                        "a"
                    ]
                }
            },
            "analyzer":{
                "my_analyzer":{
                    "type":"custom",
                    "char_filter":[
                        "html_strip",
                        "&_to_and"
                    ],
                    "tokenizer":"standard",
                    "filter":[
                        "lowercase",
                        "my_stopwords"
                    ]
                }
            }
        }
    }
}
```

# index mapping 

mapping is like a schema definition in relatinal database.

## check the mapping of an index

```bash

GET movies/_mapping

```

## dynamic mapping

if you don't specify a mapping while creating an index, a dynamic mapping would be applied.

## define the mapping explicitly

```
{
    "mappings":{
        "properties":{
            "name":{
                "type":"text"
            },
            "sex":{
                "type":"keyword"
            },
            "age":{
                "type":"integer"
            },
            "weight":{
                "type":"float"
            },
            "phone":{
                "type":"text",
                "index":false
            }
        }
    }
}
  
```

> the `keyword` type won'd be analyzed during the index.

## update the mapping

- for new fields
    - dynamic == true
        - mapping file will be updated
    - dynamic == false
        - mapping won't be updated, new added fileds cannot be indexed(but the data will show in _source field)
    - dynamic == strict
        - document creation failed
- for existing fields
    - the mapping CANNOT be updated once there are data
        - the underlying Lucene reversed index cannot be modified after creation.
    - you must do re-index if you want to update mapping of existing fields 

when there are new fileds in the request:

| dynamic                | true | false | strict |
|-----------------------:|-----:|------:| ------:|
|document can be indexed |  YES  | YES   | NO     |
|new field can be indexed | YES  | NO   | NO     |
|mapping can be updated  |  YES  | NO    | NO     |


# create the index with mapping, analyzer and shard settings

```
{
    "settings":{
        "index":{
            "number_of_shards":3,
            "number_of_replicas":2
        },
        "analysis":{
            "char_filter":{
                "&_to_and":{
                    "type":"mapping",
                    "mappings":[
                        "&=> and "
                    ]
                }
            },
            "filter":{
                "my_stopwords":{
                    "type":"stop",
                    "stopwords":[
                        "the",
                        "a"
                    ]
                }
            },
            "analyzer":{
                "my_analyzer":{
                    "type":"custom",
                    "char_filter":[
                        "html_strip",
                        "&_to_and"
                    ],
                    "tokenizer":"standard",
                    "filter":[
                        "lowercase",
                        "my_stopwords"
                    ]
                }
            }
        }
    },
    "mappings":{
        "properties":{
            "name":{
                "type":"text",
                "analyzer":"my_analyzer",
                "search_analyzer":"standard"
            },
            "sex":{
                "type":"keyword"
            },
            "age":{
                "type":"integer"
            },
            "weight":{
                "type":"float"
            },
            "phone":{
                "type":"text",
                "index":false
            }
        }
    }
}


```

# index template

Index templates allow you to define templates that will automatically be applied when new indices are created.

## create a template

```
PUT _template/t1 
{
    "index_patterns":[
        "example*",
        "test*"
    ],
    "settings":{
        "index":{
            "number_of_shards":3,
            "number_of_replicas":2
        },
        "analysis":{
            "char_filter":{
                "&_to_and":{
                    "type":"mapping",
                    "mappings":[
                        "&=> and "
                    ]
                }
            },
            "filter":{
                "my_stopwords":{
                    "type":"stop",
                    "stopwords":[
                        "the",
                        "a"
                    ]
                }
            },
            "analyzer":{
                "my_analyzer":{
                    "type":"custom",
                    "char_filter":[
                        "html_strip",
                        "&_to_and"
                    ],
                    "tokenizer":"standard",
                    "filter":[
                        "lowercase",
                        "my_stopwords"
                    ]
                }
            }
        }
    },
    "mappings":{
        "properties":{
            "name":{
                "type":"text",
                "analyzer":"my_analyzer",
                "search_analyzer":"standard"
            },
            "sex":{
                "type":"keyword"
            },
            "age":{
                "type":"integer"
            },
            "weight":{
                "type":"float"
            },
            "phone":{
                "type":"text",
                "index":false
            }
        }
    }
}
```

## check the template

```
GET /_template
GET /_template/t1
GET /_template/t*
GET /_template/t1,t2

```
## delete a template

```
DELETE /_template/t1

```

## multiple templates matching

Multiple index templates can potentially match an index, in this case, both the settings and mappings are merged into the final configuration of the index. The order of the merging can be controlled using the order parameter, with lower order being applied first, and higher orders overriding them

```
PUT /_template/t1
{
    "index_patterns" : ["*"],
    "order" : 0,
    "settings" : {
        "number_of_shards" : 1
    },
    "mappings" : {
        "_source" : { "enabled" : false }
    }
}

PUT /_template/template_2
{
    "index_patterns" : ["test*"],
    "order" : 1,
    "settings" : {
        "number_of_shards" : 2
    },
    "mappings" : {
        "_source" : { "enabled" : true }
    }
}
```
The above will disable storing the *_source* , but for indices that start with *test*, *_source* will still be enabled, and number_of_shards would be set as 2
