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
    // 2 x nth_element was a tiny bit faster for my data
//     std::sort(v.begin(), v.end());
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

double finish_line(char *buf, const char *s) {
    strcpy(buf, s);
    char c, *tmp = buf + strlen(s);
    while (c = getc_unlocked(stdin), c != EOF && c != '\n') {
        *tmp++ = c;
    }
    *tmp = '\0';
    return atof(buf);
}

int main() {
    char buf[BUF_SIZE], key[BUF_SIZE];
    int nread, prefix = 0;

    strcpy(key, "");
    std::vector<double> numbers;
    while (nread = fread(buf + prefix, 1, sizeof buf - prefix - 1, stdin), nread) {
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
//                    for (auto&& n : numbers) {
//                        printf(" %lf\n", n);
//                    }
//                    puts("");
                }
                numbers.clear();
                strcpy(key, s);
            }

            s = strsep(&n, "\n");
            if (!n) {
                double f = finish_line(buf, s);
                if(buf[0] != '\0') {
                    numbers.push_back(f);
                }
                break;
            }
            numbers.push_back(atof(s));
        }
    }
    if (!numbers.empty()) {
//        printf("%s %ld %lf %lf\n", key, numbers.size(), mean(numbers), median(numbers));
        printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
//        for (auto&& n : numbers) {
//            printf(" %lf\n", n);
//        }
//        puts("");
    }
}
