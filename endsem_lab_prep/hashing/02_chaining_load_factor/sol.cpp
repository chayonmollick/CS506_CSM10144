// 02. Chaining with search/delete queries, then load factor and longest chain (STL lists)
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin >> m >> n;
    vector<list<int> > T(m);
    int stored = 0;                                   // keys currently in the table
    for (int t = 0; t < n; t++) {
        int k;
        cin >> k;
        list<int>& c = T[((k % m) + m) % m];
        bool present = false;
        for (list<int>::iterator it = c.begin(); it != c.end(); ++it)
            if (*it == k) present = true;
        if (!present) { c.push_front(k); stored++; }  // insert at the head
    }
    int q;
    cin >> q;
    while (q--) {
        char op;
        int k;
        cin >> op >> k;
        list<int>& c = T[((k % m) + m) % m];
        list<int>::iterator it = c.begin();
        while (it != c.end() && *it != k) ++it;
        if (it == c.end()) { cout << "NOT FOUND\n"; continue; }
        if (op == 'S') cout << "FOUND\n";
        else { c.erase(it); stored--; cout << "DELETED\n"; }
    }
    int best = 0;                                     // slot of the longest chain (smallest on ties)
    for (int i = 0; i < m; i++) {
        cout << i << ":";
        for (list<int>::iterator it = T[i].begin(); it != T[i].end(); ++it) cout << " " << *it;
        cout << "\n";
        if (T[i].size() > T[best].size()) best = i;
    }
    cout << fixed << setprecision(2) << "Load factor: " << (double)stored / m << "\n";
    cout << "Longest chain: slot " << best << ", length " << T[best].size() << "\n";
    return 0;
}
