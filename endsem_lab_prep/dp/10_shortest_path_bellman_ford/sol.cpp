// 10 Shortest path DP (Bellman-Ford, slides' SHORTEST-PATH(G, t)) + negative-cycle check + PRINT-PATH
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge { int u, v; long long c; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<Edge> E(m);
    for (int k = 0; k < m; k++) cin >> E[k].u >> E[k].v >> E[k].c;
    int s, t;
    cin >> s >> t;

    const long long INF = LLONG_MAX / 4;
    vector<long long> M(n + 1, INF);  // M[v] = cost of the best v -> t path found so far
    vector<int> first(n + 1, 0);      // first[v] = next vertex after v on that path
    M[t] = 0;                         // base case: OPT(0, t) = 0, OPT(0, v) = infinity
    for (int i = 1; i <= n - 1; i++) {        // round i allows one more edge
        for (int k = 0; k < m; k++) {
            int v = E[k].u, w = E[k].v;
            // OPT(i, v) = min(OPT(i-1, v), c(v, w) + OPT(i-1, w))
            if (M[w] != INF && E[k].c + M[w] < M[v]) {
                M[v] = E[k].c + M[w];
                first[v] = w;
            }
        }
    }
    // round n: if anything still improves, a negative cycle can reach t
    for (int k = 0; k < m; k++) {
        if (M[E[k].v] != INF && E[k].c + M[E[k].v] < M[E[k].u]) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    if (M[s] == INF) {
        cout << "NO PATH\n";
        return 0;
    }
    cout << M[s] << "\n";
    // PRINT-PATH: follow the first-hop pointers from s until t
    cout << s;
    for (int v = s; v != t;) {
        v = first[v];
        cout << " " << v;
    }
    cout << "\n";
    return 0;
}
