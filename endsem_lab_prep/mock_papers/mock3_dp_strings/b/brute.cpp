// Checker for Mock 3 (b): reads X, Y and the program's answer from argv[1] (a file),
// verifies the string is a common supersequence of minimum length (BFS over (i,j) states),
// then echoes the answer so the differential tester can compare it.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
bool isSub(const string &s, const string &t) { size_t k = 0; for (size_t i = 0; i < t.size() && k < s.size(); i++) if (t[i] == s[k]) k++; return k == s.size(); }
int main(int argc, char **argv) {
    string X, Y; cin >> X >> Y;
    int m = X.size(), n = Y.size();
    // shortest supersequence length = BFS: each output char advances i, j or both
    vector<vector<int> > d(m + 1, vector<int>(n + 1, -1)); queue<pair<int,int> > q; d[0][0] = 0; q.push(make_pair(0, 0));
    while (!q.empty()) {
        int i = q.front().first, j = q.front().second; q.pop();
        int ni[3] = {i + 1, i, i + 1}, nj[3] = {j, j + 1, j + 1};
        for (int t = 0; t < 3; t++) {
            if (ni[t] > m || nj[t] > n) continue;
            if (t == 2 && X[i] != Y[j]) continue;
            if (d[ni[t]][nj[t]] < 0) { d[ni[t]][nj[t]] = d[i][j] + 1; q.push(make_pair(ni[t], nj[t])); }
        }
    }
    if (argc < 2) { cout << d[m][n] << '\n'; return 0; }
    ifstream f(argv[1]); int len; string s; f >> len >> s;
    if (len != d[m][n] || (int)s.size() != len || !isSub(X, s) || !isSub(Y, s)) { cout << "BAD\n"; return 1; }
    cout << len << '\n' << s << '\n';
}
