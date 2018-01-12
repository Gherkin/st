#include <iostream>
#include <string>

using namespace std;

int main() {
//    ios_base::sync_with_stdio(false);
    string s;
    long int i = 0;
    while (getline(cin, s)) {
        i += s.size();
    }
    cout << i;
}
