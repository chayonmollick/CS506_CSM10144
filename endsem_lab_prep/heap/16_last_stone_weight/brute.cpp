// Brute: sort before every smash, O(N^2 log N).
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n; cin >> n; vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    while (v.size() > 1) {
        sort(v.begin(), v.end());
        long long y = v.back(); v.pop_back(); long long x = v.back(); v.pop_back();
        if (y != x) v.push_back(y - x);
    }
    cout << (v.empty() ? 0 : v[0]) << "\n";
    return 0;
}
