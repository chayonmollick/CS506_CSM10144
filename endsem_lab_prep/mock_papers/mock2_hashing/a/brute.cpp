// Brute force for Mock 2 (a): one std::list per slot (push_front on insert).
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int m, q; cin >> m >> q;
    vector<list<long long> > t(m);
    for (int i = 0; i < q; i++) {
        char op; long long k; cin >> op >> k;
        list<long long> &c = t[((k % m) + m) % m];
        bool has = find(c.begin(), c.end(), k) != c.end();
        if (op == 'I' && !has) c.push_front(k);
        else if (op == 'D' && has) c.remove(k);
        else if (op == 'S') cout << (has ? "YES" : "NO") << '\n';
    }
    for (int s = 0; s < m; s++) {
        cout << s << ':';
        for (list<long long>::iterator it = t[s].begin(); it != t[s].end(); ++it) cout << ' ' << *it;
        cout << '\n';
    }
}
