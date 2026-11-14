// Checker for Mock 3 (a): LCS length by trying every subsequence of the shorter string,
// then re-derives the traceback answer with an independent memoised recursion
// (same tie rule: diagonal on match, else up when up >= left).
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
string X, Y; map<pair<int,int>, int> memo;
int L(int i, int j) {
    if (i == 0 || j == 0) return 0;
    pair<int,int> key(i, j);
    if (memo.count(key)) return memo[key];
    int r = X[i-1] == Y[j-1] ? L(i-1, j-1) + 1 : max(L(i-1, j), L(i, j-1));
    return memo[key] = r;
}
bool isSub(const string &s, const string &t) { size_t k = 0; for (size_t i = 0; i < t.size() && k < s.size(); i++) if (t[i] == s[k]) k++; return k == s.size(); }
int main() {
    cin >> X >> Y;
    const string &A = X.size() < Y.size() ? X : Y, &Bs = X.size() < Y.size() ? Y : X;
    int best = 0;
    for (int mask = 0; mask < (1 << A.size()); mask++) {
        string s; for (size_t i = 0; i < A.size(); i++) if (mask >> i & 1) s += A[i];
        if ((int)s.size() > best && isSub(s, Bs)) best = s.size();
    }
    if (best != L(X.size(), Y.size())) { cout << "BAD\n"; return 0; }
    int i = X.size(), j = Y.size(); string r;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) { r += X[i-1]; i--; j--; }
        else if (L(i-1, j) >= L(i, j-1)) i--; else j--;
    }
    reverse(r.begin(), r.end());
    cout << best << '\n' << (r.empty() ? "-" : r) << '\n';
}
