// Brute force for 40: enumerate every allocation (x_1, ..., x_k) with x_1 + ... + x_k <= B
#include <iostream>
#include <vector>
using namespace std;

int k, B;
vector<vector<long long> > g;
long long best = 0;

void go(int i, int left, long long total) {
    if (i == k) { if (total > best) best = total; return; }
    for (int x = 0; x <= left; x++) go(i + 1, left - x, total + g[i][x]);
}

int main() {
    cin >> k >> B;
    g.assign(k, vector<long long>(B + 1));
    for (int i = 0; i < k; i++)
        for (int x = 0; x <= B; x++) cin >> g[i][x];
    go(0, B, 0);
    cout << best << "\n";
    return 0;
}
