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
    "mappings" : {
      "properties" : {
        "name" : {
          "type" : "text"
        },
        "sex" : {
          "type" : "keyword"
        },
        "age" : {
          "type" : "integer"
        },
        "weight": {
          "type": "scaled_float"
        }
         "phone" : {
          "type" : "text",
          "index": false
        },
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
