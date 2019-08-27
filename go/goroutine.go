package main

import "fmt"
import "time"
func main() {
	
	//go1()
	go2()	
	time.Sleep(time.Millisecond)
}


func go1()  {
	for i:=0; i < 10 ; i++{
		go func(i int) {
			for {
				fmt.Printf("hello from: %d \n", i)
			}
			
		}(i)
	}
}

func go2()  {
	var array [10]int
	for i:=0; i < 10 ; i++{
		go func(i int) {
			 for {
				 array[i] ++;
			 }
		}(i)
	}
}