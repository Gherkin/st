#include <stdio.h>

int main() {
    char buf[4096];
    while (fread(buf, 1, sizeof buf, stdin))
        ;
}
