package main 

import (
	"fmt"
	"log"
	"net/http"
	"time"
	"os"
	"sync"
	)


var mutex sync.Mutex
var count int

func main() {
	
	http.HandleFunc("/", handler)
	http.HandleFunc("/help", handler)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))

}

func handler(writer http.ResponseWriter, request *http.Request) {

	mutex.Lock()
	count++
	mutex.Unlock()

	fmt.Fprintf(os.Stdout, "count: 	%d 	time:%v 	Path:  %q\n", count, time.Now() ,request.URL.Path)
	fmt.Fprintf(writer,    "count: 	%d 	time:%v 	Path:  %q\n", count, time.Now() ,request.URL.Path)
}