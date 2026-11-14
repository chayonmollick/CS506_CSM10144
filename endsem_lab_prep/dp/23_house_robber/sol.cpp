// 23. House Robber: max loot with no two adjacent houses robbed; (a) houses in a line, (b) houses in a circle
#include <iostream>
#include <vector>
using namespace std;

// best loot from houses a[lo..hi] in a line
long long robLine(const vector<long long>& a, int lo, int hi) {
    long long prev2 = 0, prev1 = 0;              // best(i-2), best(i-1); empty prefix = 0
    for (int i = lo; i <= hi; i++) {
        long long cur = max(prev1, prev2 + a[i]); // skip house i, or rob it and skip i-1
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// circle: house 0 and house n-1 are neighbours, so at least one of them is skipped
long long robCircle(const vector<long long>& a) {
    int n = a.size();
    if (n == 1) return a[0];                     // a single house has no neighbour
    return max(robLine(a, 0, n - 2), robLine(a, 1, n - 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << robLine(a, 0, n - 1) << "\n";
    cout << robCircle(a) << "\n";
    return 0;
}
