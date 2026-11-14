// 08 Optimal binary search tree: OPTIMAL-BST(p, q, n) + preorder of the root table
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;
vector<vector<int> > root;
vector<int> pre;

void preorder(int i, int j) {  // keys k_i..k_j; empty range = dummy leaf, print nothing
    if (i > j) return;
    int r = root[i][j];
    pre.push_back(r);
    preorder(i, r - 1);
    preorder(r + 1, j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<double> p(n + 1, 0), q(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 0; i <= n; i++) cin >> q[i];

    // e[i][j] = expected cost of the best tree on k_i..k_j (with d_{i-1}..d_j), w = total prob.
    vector<vector<double> > e(n + 2, vector<double>(n + 1, 0)), w = e;
    root.assign(n + 2, vector<int>(n + 1, 0));
    for (int i = 1; i <= n + 1; i++) e[i][i - 1] = w[i][i - 1] = q[i - 1];  // base: only d_{i-1}
    for (int l = 1; l <= n; l++) {                                         // number of keys
        for (int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            e[i][j] = 1e18;
            for (int r = i; r <= j; r++) {                                 // try k_r as root
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j] - EPS) {  // keep the FIRST minimum (floating tie-safe)
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    preorder(1, n);
    cout << fixed << setprecision(2) << e[1][n] << "\n";
    for (int k = 0; k < (int)pre.size(); k++) cout << (k ? " " : "") << pre[k];
    cout << "\n";
    return 0;
}
