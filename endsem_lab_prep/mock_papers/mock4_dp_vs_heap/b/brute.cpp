// Brute force for Mock 4 (b): Bellman-Ford style relaxation until nothing changes.
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int R, C; cin >> R >> C; vector<vector<long long> > g(R, vector<long long>(C));
    for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> g[i][j];
    const long long BIG = (long long)1e18; vector<vector<long long> > d(R, vector<long long>(C, BIG));
    d[0][0] = g[0][0];
    int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
    for (bool ch = true; ch; ) {
        ch = false;
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (d[i][j] < BIG)
            for (int t = 0; t < 4; t++) {
                int a = i + di[t], b = j + dj[t];
                if (a < 0 || a >= R || b < 0 || b >= C) continue;
                if (d[i][j] + g[a][b] < d[a][b]) { d[a][b] = d[i][j] + g[a][b]; ch = true; }
            }
    }
    cout << d[R - 1][C - 1] << '\n';
}
