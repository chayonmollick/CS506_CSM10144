// Brute force for 12 (n <= 18): try every subsequence, keep the longest palindrome.
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    string best;
    for (int mask = 1; mask < (1 << n); mask++) {
        string t;
        for (int i = 0; i < n; i++) if ((mask >> i) & 1) t += s[i];
        if (t.size() <= best.size()) continue;
        if (t == string(t.rbegin(), t.rend())) best = t;
    }
    cout << best.size() << "\n" << best << "\n";
    return 0;
}
