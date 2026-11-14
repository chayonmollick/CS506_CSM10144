// Brute force for 08: build EVERY binary search tree on k_1..k_n (Catalan many, n <= 8),
// compute sum (depth+1)*p + sum (depth+1)*q directly, keep the cheapest. Prints cost and preorder.
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int n;
vector<double> p, q;

struct Tree { double cost; vector<int> pre; };

// all trees on keys i..j whose root sits at depth d
vector<Tree> all(int i, int j, int d) {
    vector<Tree> res;
    if (i > j) { Tree t; t.cost = (d + 1) * q[i - 1]; res.push_back(t); return res; }
    for (int r = i; r <= j; r++) {
        vector<Tree> L = all(i, r - 1, d + 1), R = all(r + 1, j, d + 1);
        for (size_t a = 0; a < L.size(); a++)
            for (size_t b = 0; b < R.size(); b++) {
                Tree t;
                t.cost = (d + 1) * p[r] + L[a].cost + R[b].cost;
                t.pre.push_back(r);
                t.pre.insert(t.pre.end(), L[a].pre.begin(), L[a].pre.end());
                t.pre.insert(t.pre.end(), R[b].pre.begin(), R[b].pre.end());
                res.push_back(t);
            }
    }
    return res;
}

int main() {
    cin >> n;
    p.assign(n + 1, 0);
    q.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 0; i <= n; i++) cin >> q[i];
    vector<Tree> t = all(1, n, 0);
    size_t best = 0;
    for (size_t k = 1; k < t.size(); k++)
        if (t[k].cost < t[best].cost - 1e-9) best = k;
    cout << fixed << setprecision(2) << t[best].cost << "\n";
    for (size_t k = 0; k < t[best].pre.size(); k++) cout << (k ? " " : "") << t[best].pre[k];
    cout << "\n";
    return 0;
}
