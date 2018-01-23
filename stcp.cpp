#include <stdio.h>
#include <vector>
#include <numeric>
#include <algorithm>

double median(std::vector<double> &v) {
    // 2 x nth_element was a tiny bit faster for my data
    // std::sort(v.begin(), v.end());  
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    double median = v[n];
    if (v.size() % 2 == 0)
    {
        nth_element(v.begin(), v.begin() + n - 1, v.end());
        median = (v[n-1] + median) / 2.;
    }

    return median;
}

double mean(std::vector<double> &v) {
    return std::accumulate(v.begin(), v.end(), .0) / v.size();
}

int main() {
    char buf[4096];
    char key[4096];
    strcpy(key, "");
    std::vector<double> numbers;
    while (fgets(buf, sizeof buf, stdin)) {
        char *s = strtok(buf, " ");
        if (strcmp(key, s)) {  // New key
            if (!numbers.empty()) {
                printf("%s %lf %lf\n", key, mean(numbers), median(numbers));
            }
            numbers.clear();
            strcpy(key, s);
        }

        s = strtok(NULL, "");
        numbers.push_back(atof(s));
    }
}

