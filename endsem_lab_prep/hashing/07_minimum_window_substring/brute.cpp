// Brute force for 07: every window [i, j], counts compared letter by letter.
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int want[128] = {0};
    for (size_t i = 0; i < t.size(); i++) want[(int)t[i]]++;
    int n = (int)s.size(), bestL = -1, bestLen = n + 1;
    for (int i = 0; i < n; i++) {
        int have[128] = {0};
        for (int j = i; j < n; j++) {
            have[(int)s[j]]++;
            bool ok = true;
            for (int c = 0; c < 128; c++) if (have[c] < want[c]) ok = false;
            if (ok && j - i + 1 < bestLen) { bestLen = j - i + 1; bestL = i; }
        }
    }
    if (bestL < 0) cout << "-1\n";
    else cout << s.substr(bestL, bestLen) << "\n";
    return 0;
}
