#include <stdio.h>

int main(void) {
    char c;
    int i = 0;
    while (c = getc_unlocked(stdin), c != EOF)
        if(c == '\n')
            i++;
    printf("%d\n", i);
}
