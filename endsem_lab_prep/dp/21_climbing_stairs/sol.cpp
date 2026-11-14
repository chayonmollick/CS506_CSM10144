// 21. Climbing Stairs: ways to climb n steps with 1/2-steps, and with 1..k-steps (mod 1e9+7)
#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007LL;

// ways(i) = ways(i-1) + ways(i-2): the last step was a 1-step or a 2-step
long long climb12(int n) {
    long long prev2 = 1, prev1 = 1;              // ways(0) = 1, ways(1) = 1
    for (int i = 2; i <= n; i++) {
        long long cur = (prev1 + prev2) % MOD;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ways[i] = ways[i-1] + ways[i-2] + ... + ways[i-k]  (only terms with i-s >= 0)
long long climbK(int n, int k) {
    vector<long long> ways(n + 1, 0);
    ways[0] = 1;                                 // base case: one way to stand at the bottom
    for (int i = 1; i <= n; i++)
        for (int s = 1; s <= k && s <= i; s++)
            ways[i] = (ways[i] + ways[i - s]) % MOD;
    return ways[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    cout << climb12(n) << "\n";
    cout << climbK(n, k) << "\n";
    return 0;
}
