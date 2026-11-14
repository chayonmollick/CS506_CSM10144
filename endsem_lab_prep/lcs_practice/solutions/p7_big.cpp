// P7: LCS length of long strings with two rows: O(n) memory instead of O(mn).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = X.size(), n = Y.size();
    vector<int> prev(n + 1, 0), cur(n + 1, 0);      // prev = row i-1, cur = row i
    for (int i = 1; i <= m; i++) {
        cur[0] = 0;
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) cur[j] = prev[j - 1] + 1;
            else cur[j] = max(prev[j], cur[j - 1]);
        swap(prev, cur);
    }
    cout << prev[n] << '\n';
    return 0;
}
