// Brute force for 09: naive matcher, compare P at every shift.
#include <iostream>
#include <string>
using namespace std;

int main() {
    string T, P;
    getline(cin, T);
    getline(cin, P);
    if (!T.empty() && T[T.size() - 1] == '\r') T.erase(T.size() - 1);
    if (!P.empty() && P[P.size() - 1] == '\r') P.erase(P.size() - 1);
    int n = (int)T.size(), m = (int)P.size(), found = 0;
    for (int s = 0; s + m <= n; s++) {
        bool ok = true;
        for (int k = 0; k < m; k++) if (T[s + k] != P[k]) ok = false;
        if (ok) { cout << (found ? " " : "") << s; found++; }
    }
    if (!found) cout << -1;
    cout << "\n";
    return 0;
}
