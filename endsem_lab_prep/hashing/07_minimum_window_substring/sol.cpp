// 07. Minimum window substring: shortest window of s containing every char of t (with multiplicity)
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
    int need[128] = {0};                   // need[c] > 0: still missing that many c's
    for (size_t i = 0; i < t.size(); i++) need[(int)t[i]]++;
    int missing = (int)t.size();           // total characters still missing
    int n = (int)s.size(), bestLen = n + 1, bestL = 0, l = 0;
    for (int r = 0; r < n; r++) {
        int c = s[r];
        if (need[c] > 0) missing--;        // s[r] covers a needed character
        need[c]--;
        while (missing == 0) {             // window [l, r] is valid: shrink from the left
            if (r - l + 1 < bestLen) { bestLen = r - l + 1; bestL = l; }
            int d = s[l];
            need[d]++;
            if (need[d] > 0) missing++;    // removed a character we needed
            l++;
        }
    }
    if (bestLen > n) cout << "-1\n";
    else cout << s.substr(bestL, bestLen) << "\n";
    return 0;
}
