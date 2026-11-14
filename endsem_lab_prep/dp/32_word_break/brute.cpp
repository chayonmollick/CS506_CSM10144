// Brute force for 32: enumerate every segmentation recursively (shorter first word first)
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string s;
set<string> dict;
long long countAll = 0;
vector<string> cur, firstFound;

void rec(size_t i) {
    if (i == s.size()) {
        if (countAll == 0) firstFound = cur;       // first complete split in this order = canonical
        countAll++;
        return;
    }
    for (size_t L = 1; i + L <= s.size(); L++) {
        string w = s.substr(i, L);
        if (dict.count(w)) {
            cur.push_back(w);
            rec(i + L);
            cur.pop_back();
        }
    }
}

int main() {
    int m;
    cin >> s >> m;
    for (int i = 0; i < m; i++) { string w; cin >> w; dict.insert(w); }
    rec(0);
    if (countAll == 0) { cout << "NO\n0\n"; return 0; }
    cout << "YES\n" << countAll % 1000000007LL << "\n";
    for (size_t j = 0; j < firstFound.size(); j++) cout << (j ? " " : "") << firstFound[j];
    cout << "\n";
    return 0;
}
