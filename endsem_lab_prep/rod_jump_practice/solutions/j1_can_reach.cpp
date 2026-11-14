// J1: from index i you may jump to any of i+1 .. i+a[i]. Can index n be reached from index 1?
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long reach = 1;                                // furthest index reachable so far
    for (int i = 1; i <= n && i <= reach; i++) reach = max(reach, i + a[i]);
    cout << (reach >= n ? "YES" : "NO") << '\n';
    return 0;
}
