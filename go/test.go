package main

import "time"
import "fmt"
func main() {
	j := 0
	for i := 0; i < 10000; i++ {
		go func() {
			j++
		}()
	}
	time.Sleep(time.Second * 10)
	fmt.Println(j)
}