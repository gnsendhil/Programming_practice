package main

import (
	"fmt"
)

func main() {
	fmt.Println("Hello World!!")
	var num int
	fmt.Scanln(&num)
	res := find_prime(num)
	fmt.Println(res)
}

func find_prime(num int) bool {

	for i := 2; i <= num/2; i++ {
		if num%i == 0 {
			return false
		}
	}
	return true

}
