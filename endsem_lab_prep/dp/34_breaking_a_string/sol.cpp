// 34. Breaking a String: minimum total cost of the breaks (interval DP) and one optimal order
#include <iostream>
#include <vector>
using namespace std;

vector<long long> b;                  // piece boundaries: b[0] = 0, b[1..m] = breaks, b[m+1] = n
vector<vector<int> > split;           // split[i][j] = index of the first break done inside (b[i], b[j])
vector<long long> order;

// preorder of the split tree: break of this piece, then the left piece, then the right piece
void buildOrder(int i, int j) {
    if (j - i < 2) return;            // no break strictly between b[i] and b[j]
    int k = split[i][j];
    order.push_back(b[k]);
    buildOrder(i, k);
    buildOrder(k, j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    int m;
    cin >> n >> m;
    b.assign(m + 2, 0);
    for (int i = 1; i <= m; i++) cin >> b[i];
    b[m + 1] = n;

    // cost[i][j] = min cost to do all breaks strictly inside the piece (b[i], b[j]); base cost[i][i+1] = 0
    vector<vector<long long> > cost(m + 2, vector<long long>(m + 2, 0));
    split.assign(m + 2, vector<int>(m + 2, 0));
    for (int len = 2; len <= m + 1; len++)            // shorter pieces first
        for (int i = 0; i + len <= m + 1; i++) {
            int j = i + len;
            long long best = -1;
            for (int k = i + 1; k < j; k++) {         // try b[k] as the first break of this piece
                long long c = cost[i][k] + cost[k][j];
                if (best < 0 || c < best) { best = c; split[i][j] = k; }   // strict <: leftmost on ties
            }
            cost[i][j] = (b[j] - b[i]) + best;        // the first break costs the piece length
        }

    buildOrder(0, m + 1);
    cout << cost[0][m + 1] << "\n";
    for (size_t t = 0; t < order.size(); t++) cout << (t ? " " : "") << order[t];
    cout << "\n";
    return 0;
}
