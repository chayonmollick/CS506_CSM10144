// Brute: same rule with a linear scan over the 26 counts (no heap), O(26 N).
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s; cin >> s; int n = s.size(), cnt[26] = {0}, mx = 0;
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    for (int c = 0; c < 26; c++) if (cnt[c] > mx) mx = cnt[c];
    if (mx > (n + 1) / 2) { cout << "IMPOSSIBLE\n"; return 0; }
    string res; int prev = -1;
    for (int step = 0; step < n; step++) {
        int best = -1;
        for (int c = 0; c < 26; c++)
            if (c != prev && cnt[c] > 0 && (best < 0 || cnt[c] > cnt[best])) best = c;
        res += (char)('a' + best); cnt[best]--; prev = best;
    }
    cout << res << "\n";
    return 0;
}
