// Brute: count with std::map, sort all distinct values by (-freq, value).
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
bool cmp(const pair<long long, int>& a, const pair<long long, int>& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}
int main() {
    int n, k; cin >> n >> k; map<long long, int> f;
    for (int i = 0; i < n; i++) { long long x; cin >> x; f[x]++; }
    vector<pair<long long, int> > v(f.begin(), f.end());
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < k; i++) cout << v[i].first << (i + 1 < k ? " " : "\n");
    return 0;
}
