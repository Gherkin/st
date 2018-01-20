#include <stdio.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string.h>

const int BUF_SIZE = 4096;

double median(std::vector<double> &v) {
    // 2 x nth_element was a tiny bit faster for my data
    // std::sort(v.begin(), v.end());  
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    double median = v[n];
    if (v.size() % 2 == 0) {
        nth_element(v.begin(), v.begin() + n - 1, v.end());
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
//    printf(" >> finish_line: ['%s']\n", tmp);
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

//    fprintf(stderr, " >> %ld\n", ftell(file));
    strcpy(key, "");
    std::vector<double> numbers;
    while (true) {
        long spare_buf = sizeof buf - prefix - 1;
        nread = fread(buf + prefix, 1, std::min(spare_buf, count), file);
        if (nread == 0) {
            break;
        }
        count -= nread;
//        fprintf(stderr, " >>> %ld %ld %ld\n", nread, count, ftell(file));
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
//                    printf("%s %ld %lf %lf\n", key, numbers.size(), mean(numbers), median(numbers));
                    printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
//                    for (auto &&n : numbers) {
//                        printf(" %lf\n", n);
//                    }
//                    puts("");
                }
                numbers.clear();
                strcpy(key, s);
            }

            s = strsep(&n, "\n");
            if (!n) {
                double f = finish_line(file, buf, s, count);
                if(buf[0] != '\0') {
//                    printf(" - %lf\n", f);
                    numbers.push_back(f);
                }
                break;
            }
            double f = atof(s);
//            printf(" -- %lf\n", f);
            numbers.push_back(f);
        }
    }
    if (!numbers.empty()) {
//        printf("%s %ld %lf %lf\n", key, numbers.size(), mean(numbers), median(numbers));
        printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
//        for (auto &&n : numbers) {
//            printf("%lf\n", n);
//        }
//        puts("");
    }
//    fprintf(stderr, " >> %ld\n", ftell(file));
}
