#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        puts("usage: split filename N");
        exit(1);
    }

    char *filename = argv[1];
    int n = atoi(argv[2]);

    FILE *f = fopen(filename, "r");
    fseek(f, 0L, SEEK_END);
    long m = ftell(f) / n;
    rewind(f);
    char buf[1024];
    char buf2[1024];

    long prev = 0, cur;
    for (int i = 0; i < n; i++) {
        fseek(f, m, SEEK_CUR);
        int c;
        while (c = getc_unlocked(f), c != '\n' && c != EOF)
            ;
        if (c == EOF) {
            break;
        }
        char *line = fgets(buf, sizeof buf, f);
        char *key = strsep(&line, " ");
        while (1) {
            cur = ftell(f);
            char *line2 = fgets(buf2, sizeof buf2, f);
            char *newkey = strsep(&line2, " ");
            if (strcmp(key, newkey)) {
                printf("%s %ld %ld\n", filename, prev, cur - prev);
                prev = cur + 1;
                break;
            }
        }
    }

    fseek(f, 0L, SEEK_END);
    printf("%s %ld %ld\n", filename, prev, ftell(f) - prev);

    fclose(f);
    return 0;
}
