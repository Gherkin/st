#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[1024];
    int i = 0;
    int nread;
    while (nread = fread(buf, 1, sizeof buf, stdin), nread) {
        for(int j = 0; j < nread; j++) {
            if(buf[j] == '\n')
                i++;
        }
    }
    printf("%d\n", i);
}

