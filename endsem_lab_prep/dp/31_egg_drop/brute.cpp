// Brute force for 31: memoised recursion straight from the definition (small k, N)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > memo;

int drops(int e, int n) {                    // min worst-case drops, e eggs, n unknown floors
    if (n == 0) return 0;
    if (e == 0) return 1000000;              // impossible (never chosen when e >= 1)
    int& r = memo[e][n];
    if (r >= 0) return r;
    r = 1000000;
    for (int x = 1; x <= n; x++)
        r = min(r, 1 + max(drops(e - 1, x - 1), drops(e, n - x)));
    return r;
}

int main() {
    int k, N;
    cin >> k >> N;
    memo.assign(k + 1, vector<int>(N + 1, -1));
    cout << drops(k, N) << "\n";
    return 0;
}
