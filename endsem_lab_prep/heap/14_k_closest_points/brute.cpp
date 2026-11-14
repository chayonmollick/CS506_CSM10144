// Brute: sort all points by (x^2 + y^2, x, y) and print the first K.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct P { long long x, y; };
bool cmp(const P& a, const P& b) {
    long long da = a.x * a.x + a.y * a.y, db = b.x * b.x + b.y * b.y;
    if (da != db) return da < db;
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
int main() {
    int n, k; cin >> n >> k; vector<P> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < k; i++) cout << v[i].x << " " << v[i].y << "\n";
    return 0;
}
