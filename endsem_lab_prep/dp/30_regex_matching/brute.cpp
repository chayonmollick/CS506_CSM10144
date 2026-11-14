// Brute force for 30: plain backtracking (no memo), exponential in the worst case
#include <iostream>
#include <string>
using namespace std;

string s, p;

bool match(size_t i, size_t j) {                     // does s[i..] match p[j..] ?
    if (j == p.size()) return i == s.size();
    bool first = i < s.size() && (p[j] == '.' || p[j] == s[i]);
    if (j + 1 < p.size() && p[j + 1] == '*')
        return match(i, j + 2) || (first && match(i + 1, j));
    return first && match(i + 1, j + 1);
}

int main() {
    cin >> s >> p;
    cout << (match(0, 0) ? "YES" : "NO") << "\n";
    return 0;
}
