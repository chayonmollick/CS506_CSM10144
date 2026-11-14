// Brute force for 39: list every right/down path avoiding blocked cells, try every pair (n <= 5)
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int> > g;
vector<vector<pair<int, int> > > paths;
vector<pair<int, int> > cur;

void dfs(int i, int j) {
    if (i >= n || j >= n || g[i][j] == -1) return;
    cur.push_back(make_pair(i, j));
    if (i == n - 1 && j == n - 1) paths.push_back(cur);
    else { dfs(i + 1, j); dfs(i, j + 1); }
    cur.pop_back();
}

int main() {
    cin >> n;
    g.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> g[i][j];
    dfs(0, 0);
    long long best = -1;
    for (size_t a = 0; a < paths.size(); a++)
        for (size_t b = 0; b < paths.size(); b++) {
            vector<vector<int> > used(n, vector<int>(n, 0));
            long long total = 0;
            for (size_t q = 0; q < paths[a].size(); q++) used[paths[a][q].first][paths[a][q].second] = 1;
            for (size_t q = 0; q < paths[b].size(); q++) used[paths[b][q].first][paths[b][q].second] = 1;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (used[i][j]) total += g[i][j];
            if (total > best) best = total;
        }
    cout << best << "\n";
    return 0;
}
