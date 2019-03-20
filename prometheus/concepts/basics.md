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
#### automatically generated labels and time series

When Prometheus scrapes a target, it attaches some labels automatically to the scraped time series which serve to identify the scraped target
- job: The configured job name that the target belongs to.
- instance: The <host>:<port> part of the target's URL that was scraped.

### metric types

#### Counter

represent a  monotonically increasing counter(单调递增计数器) whose value can only increase or be reset to zero after restart.

![counter with reset](../dist/p_counter_20190320161000.png?raw=true)


references
- https://www.youtube.com/watch?v=67Ulrq6DxwA
- https://www.robustperception.io/how-does-a-prometheus-counter-work

#### Guage
A gauge is a metric that represents a single numerical value that can arbitrarily go up and down.

Gauges are typically used for measured values like temperatures or current memory usage

#### Histogram
A histogram samples observations (usually things like request durations or response sizes) and counts them in configurable buckets. It also provides a sum of all observed values.

A histogram with a base metric name of <basename> exposes multiple time series during a scrape
 - cumulative counters for the observation buckets, exposed as <basename>_bucket{le="<upper inclusive bound>"}
 - the total sum of all observed values, exposed as <basename>_sum
 - the count of events that have been observed, exposed as <basename>_count (identical to <basename>_bucket{le="+Inf"} above)
  
usages
- https://povilasv.me/prometheus-tracking-request-duration/
- https://prometheus.io/docs/practices/histograms/

#### Summary
Similar to a histogram, a summary samples observations (usually things like request durations and response sizes). While it also provides a total count of observations and a sum of all observed values, it calculates configurable quantiles over a sliding time window.

A summary with a base metric name of <basename> exposes multiple time series during a scrape
 - streaming φ-quantiles (0 ≤ φ ≤ 1) of observed events, exposed as <basename>{quantile="<φ>"}
 - the total sum of all observed values, exposed as <basename>_sum
 - the count of events that have been observed, exposed as <basename>_count
