// 09. Rabin-Karp: every 0-based shift where pattern P occurs in text T
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long D = 256;             // radix (alphabet size)
const long long Q = 1000000007LL;    // prime modulus

void readLine(string& x) {
    getline(cin, x);
    if (!x.empty() && x[x.size() - 1] == '\r') x.erase(x.size() - 1);   // Windows line ending
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string T, P;
    readLine(T);
    readLine(P);
    int n = (int)T.size(), m = (int)P.size();
    vector<int> shifts;
    if (m <= n) {
        long long h = 1;                                   // D^(m-1) mod Q
        for (int i = 1; i < m; i++) h = h * D % Q;
        long long p = 0, t = 0;                            // hash of P and of T[0..m-1]
        for (int i = 0; i < m; i++) {
            p = (p * D + (unsigned char)P[i]) % Q;
            t = (t * D + (unsigned char)T[i]) % Q;
        }
        for (int s = 0; s <= n - m; s++) {
            if (p == t && T.compare(s, m, P) == 0)         // equal hash may be spurious: verify
                shifts.push_back(s);
            if (s < n - m) {                               // roll: drop T[s], add T[s+m]
                t = (t - (unsigned char)T[s] * h % Q + Q) % Q;
                t = (t * D + (unsigned char)T[s + m]) % Q;
            }
        }
    }
    if (shifts.empty()) { cout << "-1\n"; return 0; }
    for (size_t i = 0; i < shifts.size(); i++) cout << (i ? " " : "") << shifts[i];
    cout << "\n";
    return 0;
}
