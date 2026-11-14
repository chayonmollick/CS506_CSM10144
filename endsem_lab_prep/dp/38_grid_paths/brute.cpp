// Brute force for 38: DFS over every right/down path, tracking the sum (small grids only)
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int> > a;
long long best = -1, cnt = 0;

void dfs(int i, int j, long long sum) {
    if (i >= n || j >= m || a[i][j] == -1) return;
    sum += a[i][j];
    if (i == n - 1 && j == m - 1) {
        cnt++;
        if (best < 0 || sum < best) best = sum;
        return;
    }
    dfs(i + 1, j, sum);
    dfs(i, j + 1, sum);
}

int main() {
    cin >> n >> m;
    a.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    dfs(0, 0, 0);
    cout << best << "\n" << cnt % 1000000007LL << "\n";
    return 0;
}
