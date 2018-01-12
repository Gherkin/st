package main

import (
    //"strings"
    "fmt"
    //"strconv"
    "bufio"
    "io"
    "log"
    "os"
    "bytes"
)

func main() {
    r := bufio.NewReader(os.Stdin)
    current_key := []byte(nil)
    var numbers []string
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
                fmt.Printf("%s%f%f\n", string(current_key), numbers[0], numbers[0])
            }
            current_key = make([]byte, len(key))
            copy(current_key, key)
            // TODO: print mean and median
            numbers = make([]string, 0, 100)
        }
        val, err := r.ReadString('\n')
        if err != nil {
            if err == io.EOF {
                break
            }
            log.Fatal(err)
        }
        //number := strings.TrimSpace(val)
        //f, err := strconv.ParseFloat(number, 64)
        //if err != nil {
            //log.Fatal(err)
        //}
        numbers = append(numbers, val)
    }
}

