#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[1024];
    int i = 0;
    while (fgets(buf, sizeof buf, stdin))
        ++i;
    printf("%d\n", i);
}
