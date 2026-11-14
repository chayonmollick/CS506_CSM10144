// Brute force for 14 (small n, W): try every vector of copy counts.
#include <iostream>
#include <vector>
using namespace std;

int n, W;
vector<int> w, cnt, bestCnt;
vector<long long> v;
long long best = -1;

void go(int i, int cap, long long val) {     // decide how many copies of item i
    if (i > n) {
        if (val > best) { best = val; bestCnt = cnt; }
        return;
    }
    for (int k = 0; k * w[i] <= cap; k++) {
        cnt[i] = k;
        go(i + 1, cap - k * w[i], val + k * v[i]);
    }
    cnt[i] = 0;
}

int main() {
    cin >> n >> W;
    w.assign(n + 1, 0); v.assign(n + 1, 0); cnt.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    go(1, W, 0);
    cout << best << "\n";
    for (int i = 1; i <= n; i++) cout << (i > 1 ? " " : "") << bestCnt[i];
    cout << "\n";
    return 0;
}
