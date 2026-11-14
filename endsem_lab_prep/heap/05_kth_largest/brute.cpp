// Brute: sort every prefix in descending order and read index k-1.
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    int n, k; cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> res;
    for (int i = k; i <= n; i++) {
        vector<long long> b(a.begin(), a.begin() + i);
        sort(b.begin(), b.end(), greater<long long>());
        res.push_back(b[k - 1]);
    }
    cout << res.back() << "\n";
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? " " : "\n");
    return 0;
}
