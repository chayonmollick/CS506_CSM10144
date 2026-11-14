// Brute force for 29: try every burst order (n <= 8) by recursion on the remaining list
#include <iostream>
#include <vector>
using namespace std;

long long best(vector<long long> b) {
    if (b.empty()) return 0;
    long long res = 0;
    for (size_t i = 0; i < b.size(); i++) {
        long long left = (i == 0) ? 1 : b[i - 1];
        long long right = (i + 1 == b.size()) ? 1 : b[i + 1];
        vector<long long> rest = b;
        rest.erase(rest.begin() + i);
        long long c = left * b[i] * right + best(rest);
        if (c > res) res = c;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    cout << best(b) << "\n";
    return 0;
}
