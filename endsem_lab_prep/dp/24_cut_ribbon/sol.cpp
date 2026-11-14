// 24. Cut Ribbon (CF 189A): cut length n into pieces of length a, b or c; maximise the number of pieces
#include <iostream>
#include <vector>
using namespace std;

const int NEG = -1000000000;                     // "impossible" (minus infinity)

int maxPieces(int n, int a, int b, int c) {
    int len[3] = {a, b, c};
    vector<int> dp(n + 1, NEG);                  // dp[x] = max pieces for length exactly x
    dp[0] = 0;                                   // base case: length 0 = zero pieces
    for (int x = 1; x <= n; x++)
        for (int t = 0; t < 3; t++)              // the last piece has length len[t]
            if (x >= len[t] && dp[x - len[t]] != NEG)
                dp[x] = max(dp[x], dp[x - len[t]] + 1);
    return dp[n] == NEG ? -1 : dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    cout << maxPieces(n, a, b, c) << "\n";
    return 0;
}
