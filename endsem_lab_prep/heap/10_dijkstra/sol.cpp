// 10. Dijkstra's shortest paths (directed graph, non-negative weights) with a min-heap.
// STL has no decrease-key, so push a new (dist, vertex) and skip stale entries (lazy deletion).
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

typedef pair<long long, int> State;   // (distance, vertex)
const long long UNSEEN = -1;          // distance of a vertex not reached yet

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, long long> > > adj(n + 1);   // adj[u] = (v, w)
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));               // undirected: also push (u, w) to adj[v]
    }
    vector<long long> dist(n + 1, UNSEEN);
    priority_queue<State, vector<State>, greater<State> > pq;   // min-heap on distance
    dist[s] = 0;
    pq.push(make_pair(0LL, s));
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d != dist[u]) continue;                      // stale entry: u already finalised
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            long long nd = d + adj[u][i].second;
            if (dist[v] == UNSEEN || nd < dist[v]) {        // RELAX(u, v)
                dist[v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << dist[i] << (i < n ? ' ' : '\n');
    return 0;
}
