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

## removal of index types

before 7.0, an index can be defined with many kind of Types,

after 7.0, type can only be `_doc`, see https://www.elastic.co/guide/en/elasticsearch/reference/6.0/removal-of-types.html for more information
