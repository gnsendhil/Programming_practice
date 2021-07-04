/*
 *Read input from STDIN. Print your output to STDOUT
 *Use fmt.Scanf to read input from STDIN and fmt. Println to write output to STDOUT
 */

package main

import (
	"fmt"
	"math"
)

func main() {
	var N int
	fmt.Scanf("%d", &N)
	arr := make([]int, N)
	count := 0
	for i := 0; i < N; i++ {
		fmt.Scanf("%d", &arr[i])
		count += count_moves(arr[i])
	}
	fmt.Print(count)
}

func count_moves(res int) int {
	var sarr [50]int
	length := 0
	var divider int
	divider = 2

	if is_prime_number(res) == true {
		return res + 1
	}

	for res > 1 {
		if res%divider == 0 {
			res = res / divider
			sarr[length] = divider
			length = length + 1
		} else {
			divider = divider + 1
		}
		if divider > int(math.Sqrt(float64(res))) {
			divider = res
		}
	}
	multiplier := 1
	move_count := 1
	for i := length - 1; i >= 0; i-- {
		move_count = move_count + (multiplier * sarr[i])
		multiplier = multiplier * sarr[i]
	}
	//fmt.Println(sarr)
	//fmt.Println(len(sarr))
	//fmt.Println(move_count)
	return move_count
}

func is_prime_number(num int) bool {

	if num <= 1 {
		return false
	}

	sqrt := math.Sqrt(float64(num))
	for i := 2; i <= int(sqrt); i++ {
		if num%i == 0 {
			return false
		}
	}

	return true
}
