// 32. Word Break: decide, count segmentations (mod 1e9+7), print one segmentation
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    int m;
    cin >> s >> m;
    unordered_set<string> dict;                    // dictionary in a hash set
    int maxLen = 0;
    for (int i = 0; i < m; i++) {
        string w;
        cin >> w;
        dict.insert(w);
        if ((int)w.size() > maxLen) maxLen = w.size();
    }

    int n = s.size();
    // ok[i] = suffix s[i..n) can be split; ways[i] = number of splits of s[i..n)
    vector<bool> ok(n + 1, false);
    vector<long long> ways(n + 1, 0);
    ok[n] = true;                                  // base case: empty suffix, one (empty) split
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int L = 1; L <= maxLen && i + L <= n; L++) {
            if (ok[i + L] && dict.count(s.substr(i, L))) {   // first word s[i..i+L), rest s[i+L..n)
                ok[i] = true;
                ways[i] = (ways[i] + ways[i + L]) % MOD;
            }
        }
    }

    if (!ok[0]) {
        cout << "NO\n0\n";
        return 0;
    }
    cout << "YES\n" << ways[0] << "\n";
    // reconstruction: from position i take the shortest word that leaves a splittable suffix
    int i = 0;
    bool first = true;
    while (i < n) {
        int L = 1;
        while (!(i + L <= n && ok[i + L] && dict.count(s.substr(i, L)))) L++;
        cout << (first ? "" : " ") << s.substr(i, L);
        first = false;
        i += L;
    }
    cout << "\n";
    return 0;
}
