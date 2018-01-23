#include <stdio.h>

int main() {
    char c;
    while (c = getc_unlocked(stdin), c != EOF) {
        putc_unlocked(c, stdout);
    }
}
