## time series

Data in InfluxDB is organized by “time series”

## points

Time series have zero to many points

Points are written to InfluxDB using the Line Protocol, which follows the following format

```
<measurement>[,<tag-key>=<tag-value>...] <field-key>=<field-value>[,<field2-key>=<field2-value>...] [unix-nano-timestamp]
```

A point consists of: 
- time (a timestamp)
- a measurement (“cpu_load”)
- at least one key-value field (the measured value itself, e.g. “value=0.64”, or “temperature=21.2”)
- zero to many key-value tags containing any metadata about the value (e.g. “host=server01”, “region=Tokyo”).

## measurement

Conceptually you can think of a measurement as an SQL table, where the primary index is always time.

## tag and fileds

tags and fields are effectively columns in the table.

tags are indexed, and fields are not. 

