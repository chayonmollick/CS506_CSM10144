// Brute: Bellman-Ford, O(N*M).
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, m, s; cin >> n >> m >> s;
    vector<int> U(m), V(m); vector<long long> W(m);
    for (int i = 0; i < m; i++) cin >> U[i] >> V[i] >> W[i];
    vector<long long> d(n + 1, -1); d[s] = 0;
    for (int it = 0; it < n; it++)
        for (int i = 0; i < m; i++)
            if (d[U[i]] != -1 && (d[V[i]] == -1 || d[U[i]] + W[i] < d[V[i]])) d[V[i]] = d[U[i]] + W[i];
    for (int i = 1; i <= n; i++) cout << d[i] << (i < n ? " " : "\n");
    return 0;
}
