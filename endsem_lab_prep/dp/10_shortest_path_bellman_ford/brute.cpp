// Brute force for 10 (n <= 7): enumerate every simple cycle (negative-cycle check) and every
// simple s -> t path (shortest cost). Without negative cycles a shortest path is always simple.
#include <iostream>
#include <vector>
using namespace std;

struct Edge { int u, v; long long c; };
int n, m, s, t;
vector<Edge> E;
vector<bool> used, canReachT;
bool negCycle = false;
long long best;
bool found = false;
vector<int> path, bestPath;

void cycles(int start, int v, long long cost) {   // simple paths start -> v, close back to start
    for (int k = 0; k < m; k++) {
        if (E[k].u != v) continue;
        int w = E[k].v;
        if (w == start && cost + E[k].c < 0 && canReachT[start]) negCycle = true;
        if (!used[w]) { used[w] = true; cycles(start, w, cost + E[k].c); used[w] = false; }
    }
}

void paths(int v, long long cost) {
    if (v == t) {
        if (!found || cost < best) { found = true; best = cost; bestPath = path; }
        return;
    }
    for (int k = 0; k < m; k++) {
        if (E[k].u != v || used[E[k].v]) continue;
        used[E[k].v] = true; path.push_back(E[k].v);
        paths(E[k].v, cost + E[k].c);
        used[E[k].v] = false; path.pop_back();
    }
}

int main() {
    cin >> n >> m;
    E.resize(m);
    for (int k = 0; k < m; k++) cin >> E[k].u >> E[k].v >> E[k].c;
    cin >> s >> t;
    canReachT.assign(n + 1, false);
    canReachT[t] = true;
    for (int r = 0; r < n; r++)                      // simple fixed-point reachability
        for (int k = 0; k < m; k++) if (canReachT[E[k].v]) canReachT[E[k].u] = true;
    used.assign(n + 1, false);
    for (int st = 1; st <= n; st++) { used[st] = true; cycles(st, st, 0); used[st] = false; }
    if (negCycle) { cout << "NEGATIVE CYCLE\n"; return 0; }
    used[s] = true; path.push_back(s);
    paths(s, 0);
    if (!found) { cout << "NO PATH\n"; return 0; }
    cout << best << "\n";
    for (size_t i = 0; i < bestPath.size(); i++) cout << (i ? " " : "") << bestPath[i];
    cout << "\n";
    return 0;
}
