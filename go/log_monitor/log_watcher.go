package main 

import (
    "fmt"
    "time"
    "strings"
    "os"
    "io"
    "bufio"
    "strconv"
    "regexp"
    "log"
    "net/url"
    "flag"
    "github.com/influxdata/influxdb/client/v2"
)


type Reader interface {
 	Read(readChannel chan []byte)
} 

type Writer interface {
	Write(writeChannel chan *Message)
} 

type ReadFromFile struct {
	path string
}

type WriteToInfluxDB struct {
	db string
} 


func (r *ReadFromFile) Read(readChannel chan []byte) {

	f, err := os.Open(r.path)

	if err != nil {
		panic(fmt.Sprintf("open file error: %s", err.Error()))
	}

	f.Seek(0, 2)
	reader := bufio.NewReader(f)

	for  {
		line, err := reader.ReadBytes('\n')
		if err == io.EOF {
			time.Sleep (500 * time.Millisecond)
			continue
		}else if err != nil {
			panic(fmt.Sprintf("open file error: %s", err.Error()))
		}
		readChannel <- line
	}

	
}

type LogWatcher struct {	
	readChannel chan []byte
	writeChannel chan *Message
	reader Reader
	writer Writer
}

type Message struct {
TimeLocal time.Time
BytesSent int
Path, Method, Scheme, Status string
UpstreamTime, RequestTime float64
} 

func (l *LogWatcher) Process() {

	/**
	172.0.0.12 - - [04/Mar/2018:13:49:52 +0000] http "GET /foo?query=t HTTP/1.0" 200 2133 "-" "KeepAliveClient" "-" 1.005 1.854
	*/

	regex := regexp.MustCompile(`([\d\.]+)\s+([^ \[]+)\s+([^ \[]+)\s+\[([^\]]+)\]\s+([a-z]+)\s+\"([^"]+)\"\s+(\d{3})\s+(\d+)\s+\"([^"]+)\"\s+\"(.*?)\"\s+\"([\d\.-]+)\"\s+([\d\.-]+)\s+([\d\.-]+)`)

	loc, _ := time.LoadLocation("Asia/Shanghai")

	for v := range l.readChannel {

		fields := regex.FindStringSubmatch(string(v));

		if len(fields) != 14 {
			log.Println("invalid log found:" , string(v))
			continue
		}

		message := &Message {

		}

		t, err := time.ParseInLocation("02/Jan/2006:15:04:05 +0000", fields[4], loc)
		if err != nil {
			log.Println("ParseInLocation fail:", err.Error(), fields[4])
			continue
		}
		message.TimeLocal = t
		byteSent, _ := strconv.Atoi(fields[8])
		message.BytesSent = byteSent

		// GET /foo?query=t HTTP/1.0
		reqSli := strings.Split(fields[6], " ")
		if len(reqSli) != 3 {
			log.Println("strings.Split fail", fields[6])
			continue
		}
		message.Method = reqSli[0]

		u, err := url.Parse(reqSli[1])
		if err != nil {
			log.Println("url parse fail:", err)
			continue
		}
		message.Path = u.Path

		message.Scheme = fields[5]
		message.Status = fields[7]

		upstreamTime, _ := strconv.ParseFloat(fields[12], 64)
		requestTime, _ := strconv.ParseFloat(fields[13], 64)
		message.UpstreamTime = upstreamTime
		message.RequestTime = requestTime


		l.writeChannel <-message
	}
}

func (w *WriteToInfluxDB) Write(writeChannel chan *Message) {


	dbClient := strings.Split(w.db, "@")

	// Create a new HTTPClient
	c, err := client.NewHTTPClient(client.HTTPConfig {
		Addr:     dbClient[0],
		Username: dbClient[1],
		Password: dbClient[2],
	})
	if err != nil {
		log.Fatal(err)
	}


	for v := range writeChannel {
		// Create a new point batch
		bp, err := client.NewBatchPoints(client.BatchPointsConfig{
			Database:  dbClient[3],
			Precision: dbClient[4],
		})
		if err != nil {
			log.Fatal(err)
		}

		// Create a point and add to batch
		// Tags: Path, Method, Scheme, Status
		tags := map[string]string{"Path": v.Path, "Method": v.Method, "Scheme": v.Scheme, "Status": v.Status}
		// Fields: UpstreamTime, RequestTime, BytesSent
		fields := map[string]interface{}{
			"UpstreamTime": v.UpstreamTime,
			"RequestTime":  v.RequestTime,
			"BytesSent":    v.BytesSent,
		}

		pt, err := client.NewPoint("accesslog", tags, fields, v.TimeLocal)
		if err != nil {
			log.Fatal(err)
		}
		bp.AddPoint(pt)

		// Write the batch
		if err := c.Write(bp); err != nil {
			log.Fatal(err)
		}

		log.Println("write success!")
	}

	
}




func main() {

	var path, db string
	flag.StringVar(&path, "path", "/tmp/access.log", "read file path")
	flag.StringVar(&db, "db", "http://127.0.0.1:8086@root@123456@accesslog@s", "influx data source")
	flag.Parse()

	r := &ReadFromFile {
		path: path,
	}

	w := &WriteToInfluxDB {
		db: db,
	}

	lp := &LogWatcher{
		readChannel: make(chan []byte),
		writeChannel: make(chan *Message),
		reader: r,
		writer: w,
	}

	go lp.reader.Read(lp.readChannel)
	go lp.Process()
	go lp.writer.Write(lp.writeChannel)

	time.Sleep(10 * time.Second)
}