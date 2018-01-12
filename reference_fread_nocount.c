#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[1024];
    int i = 0;
    int nread;
    while (nread = fread(buf, 1, sizeof buf, stdin), nread) {
        ++i;
    }
    printf("%d\n", i);
}

