// Mock 4 (b): cheapest path when all 4 moves are allowed. Paths can turn back, so the
// right/down DP order no longer exists; Dijkstra with a min-priority queue on the cells.
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

typedef pair<long long, int> State;   // (cost so far, cell id = i*C + j)

int main() {
    ios::sync_with_stdio(false);
    // ---- Common setup: read the grid ----
    int R, C;
    cin >> R >> C;
    vector<vector<long long> > g(R, vector<long long>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) cin >> g[i][j];
    // ---- end of common setup ----

    const long long INF = -1;          // -1 = not reached yet
    vector<long long> dist(R * C, INF);
    priority_queue<State, vector<State>, greater<State> > pq;   // min-heap on cost
    dist[0] = g[0][0];
    pq.push(State(dist[0], 0));
    int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
    while (!pq.empty()) {
        State top = pq.top();
        pq.pop();
        long long d = top.first;
        int u = top.second;
        if (d != dist[u]) continue;            // stale entry (lazy deletion)
        int i = u / C, j = u % C;
        for (int t = 0; t < 4; t++) {
            int ni = i + di[t], nj = j + dj[t];
            if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
            int v = ni * C + nj;
            long long nd = d + g[ni][nj];      // entering a cell pays its cost
            if (dist[v] == INF || nd < dist[v]) { dist[v] = nd; pq.push(State(nd, v)); }
        }
    }
    cout << dist[R * C - 1] << '\n';
    return 0;
}
