#include <stdio.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string.h>

/**
 * N.b. This is a naive program without bounds checking or similar.
 */

const int BUF_SIZE = 4096;

double median(std::vector<double> &v) {
    std::sort(v.begin(), v.end());
    size_t n = v.size() / 2;
    double median = v[n];
    if (v.size() % 2 == 0) {
        median = (v[n - 1] + median) / 2.;
    }

    return median;
}

double mean(std::vector<double> &v) {
    return std::accumulate(v.begin(), v.end(), .0) / v.size();
}

double finish_line(FILE *f, char *buf, const char *s, long &count) {
    strcpy(buf, s);
    char c, *tmp = buf + strlen(s);
    while (c = getc_unlocked(f), c != EOF && c != '\n') {
        --count;
        *tmp++ = c;
    }
    --count;
    *tmp = '\0';
    return atof(buf);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        puts("usage: ./stsplit filename offset bytecount");
        exit(1);
    }

    char *filename = argv[1];
    long offset = atol(argv[2]);
    long count = atol(argv[3]);

    FILE *file = fopen(argv[1], "r");
    fseek(file, offset, SEEK_SET);
    char buf[BUF_SIZE], key[BUF_SIZE];
    long nread, prefix = 0;

    strcpy(key, "");
    std::vector<double> numbers;
    while (true) {
        long spare_buf = sizeof buf - prefix - 1;
        nread = fread(buf + prefix, 1, std::min(spare_buf, count), file);
        if (nread == 0) {
            break;
        }
        count -= nread;
        buf[nread + prefix] = '\0';
        prefix = 0;
        char *n = buf;
        while (true) {
            char *s = strsep(&n, " ");
            if (!n) {
                // End of buffer while reading key, put the few chars back and start over...
                strcpy(buf, s);
                prefix = strlen(s);
                break;
            }

            if (strcmp(key, s)) {
                if (!numbers.empty()) {
                    printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
                }
                numbers.clear();
                strcpy(key, s);
            }

            s = strsep(&n, "\n");
            if (!n) {
                double f = finish_line(file, buf, s, count);
                if (buf[0] != '\0') {
                    numbers.push_back(f);
                }
                break;
            }
            double f = atof(s);
            numbers.push_back(f);
        }
    }
    if (!numbers.empty()) {
        printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
    }
}
