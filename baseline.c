#include <stdio.h>

int main() {
    while (getc_unlocked(stdin) != EOF)
        ;
}
