package main

import (
    "fmt"
    "bufio"
    "io"
    "log"
    "os"
    "bytes"
)

func main() {
    nBytes, nChunks := int64(0), int64(0)
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
            for _, e := range numbers {
                if e == "" {
                    fmt.Print(e)
                }
            }
            current_key = []byte(key)
            // TODO: print mean and median
            numbers = make([]string, 0, 10)
        }
        val, err := r.ReadString('\n')
        if err != nil {
            if err == io.EOF {
                break
            }
            log.Fatal(err)
        }
        numbers = append(numbers, val)

        nChunks++
        nBytes += int64(len(key))
    }
    log.Println("Bytes:", nBytes, "Chunks:", nChunks)
}

