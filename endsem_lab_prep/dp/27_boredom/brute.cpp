// Brute force for 27: play the game exhaustively (every possible move order), memoised on the multiset
#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<vector<int>, long long> memo;

long long play(const vector<int>& cnt) {        // cnt[v] = copies of value v left
    map<vector<int>, long long>::iterator it = memo.find(cnt);
    if (it != memo.end()) return it->second;
    long long best = 0;
    for (int v = 1; v + 1 < (int)cnt.size(); v++)
        if (cnt[v] > 0) {                         // move: delete one v, all v-1 and all v+1
            vector<int> next = cnt;
            next[v]--;
            next[v - 1] = 0;
            next[v + 1] = 0;
            long long got = v + play(next);
            if (got > best) best = got;
        }
    memo[cnt] = best;
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; if (a[i] > mx) mx = a[i]; }
    vector<int> cnt(mx + 2, 0);
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    cout << play(cnt) << "\n";
    return 0;
}
