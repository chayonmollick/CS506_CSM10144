// 13 Coin change: (a) min coins, (b) combinations (order ignored), (c) sequences (order matters)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, A;
    cin >> k >> A;
    vector<int> c(k);
    for (int i = 0; i < k; i++) cin >> c[i];
    const long long MOD = 1000000007LL;
    const int INF = 1000000000;

    // (a) mn[a] = fewest coins summing to a; mn[0] = 0
    vector<int> mn(A + 1, INF);
    mn[0] = 0;
    for (int a = 1; a <= A; a++)
        for (int i = 0; i < k; i++)
            if (c[i] <= a && mn[a - c[i]] + 1 < mn[a]) mn[a] = mn[a - c[i]] + 1;

    // (b) COINS OUTER: each multiset is built in coin order only -> counts combinations
    vector<long long> comb(A + 1, 0);
    comb[0] = 1;                                   // one way to make 0: take nothing
    for (int i = 0; i < k; i++)
        for (int a = c[i]; a <= A; a++)            // upward: coin i may be reused
            comb[a] = (comb[a] + comb[a - c[i]]) % MOD;

    // (c) AMOUNT OUTER: any coin may be the last one -> counts ordered sequences
    vector<long long> seq(A + 1, 0);
    seq[0] = 1;
    for (int a = 1; a <= A; a++)
        for (int i = 0; i < k; i++)
            if (c[i] <= a) seq[a] = (seq[a] + seq[a - c[i]]) % MOD;

    cout << (mn[A] >= INF ? -1 : mn[A]) << "\n";
    cout << comb[A] << "\n";
    cout << seq[A] << "\n";
    return 0;
}
