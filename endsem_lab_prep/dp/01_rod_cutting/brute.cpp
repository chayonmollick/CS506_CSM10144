// Brute force for 01: try every way to cut the rod (all 2^(n-1) compositions).
// Keeps the lexicographically smallest optimal piece sequence. Use only for n <= 15.
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> p;
long long best = -1;
vector<int> bestCut, cur;

void go(int left, long long val) {
    if (left == 0) {
        if (val > best || (val == best && cur < bestCut)) { best = val; bestCut = cur; }
        return;
    }
    for (int i = 1; i <= left; i++) {
        cur.push_back(i);
        go(left - i, val + p[i]);
        cur.pop_back();
    }
}

int main() {
    cin >> n;
    p.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];
    go(n, 0);
    cout << best << "\n";
    for (size_t i = 0; i < bestCut.size(); i++) cout << (i ? " " : "") << bestCut[i];
    cout << "\n";
    return 0;
}
