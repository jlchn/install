### data model
#### metric and time series

`metric` is the measurement of a particular characteristic of a programs performance or efficiency.

A `time series` is a series of data points indexed (or listed or graphed) in time order. Most commonly, a time series is a sequence taken at successive equally spaced points in time.

> from https://en.wikipedia.org/wiki/Time_series

each time series is called a metric and identified by a `metric name` and several `labels`(in form of key-value pairs) 
```
<metric name>{<label name>=<label value>, ...}
```

#### jobs and instances

In Prometheus terms, an endpoint you can scrape is called an instance, usually corresponding to a single process. A collection of instances with the same purpose is called a job

```
job: api-server
instance 1: 1.2.3.4:5670
instance 2: 1.2.3.4:5671
instance 3: 5.6.7.8:5670
instance 4: 5.6.7.8:5671
```
#### Automatically generated labels and time series

When Prometheus scrapes a target, it attaches some labels automatically to the scraped time series which serve to identify the scraped target
- job: The configured job name that the target belongs to.
- instance: The <host>:<port> part of the target's URL that was scraped.

### metric types

#### Counter

represent a  monotonically increasing counter(单调递增计数器) whose value can only increase or be reset to zero after restart.

@[counter with reset](../dist/p_counter_20190320161000.png)


usage: https://www.robustperception.io/how-does-a-prometheus-counter-work
