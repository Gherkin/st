package main

import (
    "fmt"
    "io"
    "log"
    "os"
    "bufio"
)

func main() {
    r := bufio.NewReader(os.Stdin)
    n := 0
    for {
        _, err := r.ReadSlice(' ')
        if err != nil {
            if err == io.EOF {
                break
            }
            log.Fatal(err)
        }
        n++
    }
    fmt.Print(n)
}

