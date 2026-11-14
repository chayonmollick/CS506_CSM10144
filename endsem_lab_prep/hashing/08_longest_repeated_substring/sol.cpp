// 08. Longest repeated substring (overlap allowed): binary search on L + Rabin-Karp rolling hash
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const long long MOD = 1000000007LL, BASE = 131;
string s;
int n;

// Start of the first occurrence of a length-L substring that occurs at least twice, or -1.
// leftmost = false: stop at the first repeat found (enough for the binary search).
// leftmost = true : scan everything and return the smallest such first occurrence.
int repeatedStart(int L, bool leftmost) {
    long long high = 1;                                // BASE^(L-1) mod MOD
    for (int i = 1; i < L; i++) high = high * BASE % MOD;
    long long h = 0;
    for (int i = 0; i < L; i++) h = (h * BASE + s[i]) % MOD;
    unordered_map<long long, vector<int> > seen;      // hash -> starts of DIFFERENT strings
    int best = -1;
    for (int i = 0; i + L <= n; i++) {
        if (i > 0) {                                   // roll: remove s[i-1], append s[i+L-1]
            h = (h - s[i - 1] * high % MOD + MOD) % MOD;
            h = (h * BASE + s[i + L - 1]) % MOD;
        }
        vector<int>& bucket = seen[h];
        bool dup = false;
        for (size_t t = 0; t < bucket.size() && !dup; t++)
            if (s.compare(bucket[t], L, s, i, L) == 0) {   // equal hash: verify characters
                dup = true;
                if (best == -1 || bucket[t] < best) best = bucket[t];
            }
        if (dup && !leftmost) return best;
        if (!dup) bucket.push_back(i);                 // new string (or a collision)
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    n = (int)s.size();
    int lo = 0, hi = n - 1;                            // length 0 always "repeats"
    while (lo < hi) {                                  // largest L with a repeat (monotone)
        int mid = (lo + hi + 1) / 2;
        if (repeatedStart(mid, false) != -1) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    if (lo > 0) cout << s.substr(repeatedStart(lo, true), lo) << "\n";
    return 0;
}
