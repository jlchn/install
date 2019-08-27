package main

import(
	"fmt"
	"io/ioutil"
	"net/http"
	"time"
)

func main() {
	
	urls := []string { "https://www.google.com", "https://github.com" }
	start := time.Now()

	channel := make(chan string) 

	//start goroutine
	for _, url:= range urls { 
		go fetch(url, channel) 
	}
	
	//receive from channel
	for range urls {
		fmt.Println(<-channel)
	}


	fmt.Printf("%2f.	elapsed\n", time.Since(start).Seconds()) //fmt.Fprintf(os.Stdout, "%s", body)
}


func fetch(url string, channel chan<- string) {
	start := time.Now()

	resp, err := http.Get(url)

	if err != nil {
		channel <- fmt.Sprintf("fetch failed:%v\n" , err);
		return
	}

	body, err := ioutil.ReadAll(resp.Body)

	if err != nil {
		channel <- fmt.Sprintf("failed to read %s, err: %v", url, err)
		return
	}

	seconds := time.Since(start).Seconds()

	channel <- fmt.Sprintf("%.2fs	%7d		%s", seconds, len(body), url)
}
