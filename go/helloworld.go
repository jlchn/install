package main

import "fmt"
import utils "./utils"

func main(){
	fmt.Println(utils.Basename("a/b/c.go"));
	fmt.Println(utils.IntsToString([]int{1,2,4}))
}