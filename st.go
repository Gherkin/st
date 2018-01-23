package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func mean(input []float64) float64 {
	sum := 0.0
	for _, i := range input {
		sum += i
	}

	return sum / float64(len(input))
}

func median(input []float64) (result float64) {
	sort.Float64s(input)
	l := len(input)
	if l%2 == 0 {
		result = mean(input[l/2-1 : l/2+1])
	} else {
		result = float64(input[l/2])
	}

	return result
}

func handle(current_key []byte, numbers []byte, messages chan bool) {
	vs2 := bytes.Split(numbers, []byte("\n"))
    vals := make([]float64, 0, 100)
	for _, v := range vs2 {
		if len(v) > 0 {
			number := strings.TrimSpace(string(v))
			f, err := strconv.ParseFloat(number, 64)
			if err != nil {
				log.Fatal(err)
			}
            vals = append(vals, f)
		}
	}
    fmt.Printf("%s%f%f\n", string(current_key), mean(vals), median(vals))
    messages <- true
}

func main() {
    messages := make(chan bool)
    num_keys := 0
	r := bufio.NewReader(os.Stdin)
	current_key := []byte(nil)
	var numbers []byte
	for {
		key, err := r.ReadSlice(' ')
		if err != nil {
			if err == io.EOF {
				break
			}
			log.Fatal(err)
		}
		if !bytes.Equal(key, current_key) {
			if len(numbers) > 0 {
				go handle(current_key, numbers, messages)
                num_keys++
            }
			current_key = make([]byte, len(key))
			copy(current_key, key)
			numbers = make([]byte, 0, 4096)
		}
		val, err := r.ReadSlice('\n')
		if err != nil {
			if err == io.EOF {
				break
			}
			log.Fatal(err)
		}
		numbers = append(numbers, val...)
	}
    for i := 0; i < num_keys; i++ {
        <-messages
    }
}

