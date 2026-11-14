// 33. Company Party: max-weight set of employees with no (employee, immediate supervisor) pair; tree DP
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    vector<vector<int> > child(n + 1);
    int root = 0;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if (p == 0) root = i;                     // the president
        else child[p].push_back(i);
    }

    // BFS order from the root: every parent comes before its children
    vector<int> order(1, root);
    for (size_t h = 0; h < order.size(); h++)
        for (size_t t = 0; t < child[order[h]].size(); t++) order.push_back(child[order[h]][t]);

    // inc[v] = best in v's subtree with v attending, exc[v] = best with v absent
    vector<long long> inc(n + 1, 0), exc(n + 1, 0);
    for (int t = n - 1; t >= 0; t--) {            // reverse BFS: children are finished before parents
        int v = order[t];
        inc[v] = c[v];                            // base (leaf): inc = c[v], exc = 0
        for (size_t q = 0; q < child[v].size(); q++) {
            int u = child[v][q];
            inc[v] += exc[u];                     // v attends -> its direct reports cannot
            exc[v] += max(inc[u], exc[u]);        // v absent -> each report is free to choose
        }
    }
    cout << max(inc[root], exc[root]) << "\n";    // (a) best party (may be empty -> 0)
    cout << inc[root] << "\n";                    // (b) president must attend
    return 0;
}
