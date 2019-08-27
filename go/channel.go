package main
import "fmt"
func chanDemo1()  {
	c := make(chan int)
	go func(){
		for {
			n := <-c
			fmt.Println(n)
		}
	}()
	c <- 1
	c <- 2
	c <- 3
	c <- 4	
}
func chanDemo0() {
	c := make(chan int)
	c <- 1 // 此时只有一个main goroutine，没有另一个 goroutine接收c中的数据
	c <- 2
	n := <-c

	fmt.Println(n)
}

func chanDemo2()  {
	c := make(chan int)
	
	c <- 1 // 此时只有一个main goroutine，没有另一个 goroutine接收c中的数据
	c <- 2
	c <- 3
	c <- 4	
	go func(){
		for {
			n := <-c
			fmt.Println(n)
		}
	}()
}

func main() {
	chanDemo2()
}