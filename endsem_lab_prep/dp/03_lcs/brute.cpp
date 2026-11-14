// Brute force for 03: try every subsequence of X (2^m, m <= 15) and keep the longest one
// that is also a subsequence of Y. Prints the length and one such subsequence.
#include <iostream>
#include <string>
using namespace std;

bool isSubseq(const string &a, const string &b) {  // is a a subsequence of b?
    size_t k = 0;
    for (size_t i = 0; i < b.size() && k < a.size(); i++)
        if (b[i] == a[k]) k++;
    return k == a.size();
}

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = (int)X.size();
    string best;
    for (int mask = 0; mask < (1 << m); mask++) {
        string t;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) t += X[i];
        if (t.size() > best.size() && isSubseq(t, Y)) best = t;
    }
    cout << best.size() << "\n" << best << "\n";
    return 0;
}
