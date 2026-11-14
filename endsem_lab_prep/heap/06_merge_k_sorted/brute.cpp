// Brute: concatenate everything and sort.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int k; cin >> k; vector<long long> all;
    for (int i = 0; i < k; i++) { int m; cin >> m; for (int j = 0; j < m; j++) { long long x; cin >> x; all.push_back(x); } }
    sort(all.begin(), all.end());
    for (size_t i = 0; i < all.size(); i++) cout << all[i] << (i + 1 < all.size() ? " " : "\n");
    return 0;
}
