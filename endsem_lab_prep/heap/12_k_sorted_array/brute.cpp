// Brute: std::sort.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n, k; cin >> n >> k; vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? " " : "\n");
    return 0;
}
