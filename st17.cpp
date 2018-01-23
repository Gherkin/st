#include <stdio.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <iostream>

double median(std::vector<double> &v) {
    size_t n = v.size() / 2;
    std::sort(v.begin(), v.end());
    nth_element(v.begin(), v.begin() + n, v.end());
    return v[n];
}

double mean(std::vector<double> &v) {
    return std::accumulate(v.begin(), v.end(), .0) / v.size();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string key = std::string("");
    std::string tmp;
    float f;
    std::vector<double> numbers;
    while (!std::cin.eof()) {
        std::cin >> tmp >> f;
        if (key != tmp) {  // New key
            if (!numbers.empty()) {
                printf("%s %lf %lf\n", key.c_str(), mean(numbers), median(numbers));
            }
            numbers.clear();
            key = tmp;
        }

        numbers.push_back(f);
    }
}
