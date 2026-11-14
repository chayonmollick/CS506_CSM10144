// Brute force for the chaining template: chains kept as std::vector, new key at index 0.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m, q;
    cin >> m >> q;
    vector<vector<int> > ch(m);
    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') {
            for (int i = 0; i < m; i++) {
                cout << i << ":";
                for (size_t t = 0; t < ch[i].size(); t++) cout << " " << ch[i][t];
                cout << "\n";
            }
            continue;
        }
        int x;
        cin >> x;
        int s = ((x % m) + m) % m;
        int pos = -1;
        for (size_t t = 0; t < ch[s].size(); t++)
            if (ch[s][t] == x) pos = (int)t;
        if (op == 'I' && pos == -1) ch[s].insert(ch[s].begin(), x);
        if (op == 'S') cout << (pos != -1 ? "FOUND" : "NOT FOUND") << "\n";
        if (op == 'D') {
            if (pos != -1) ch[s].erase(ch[s].begin() + pos);
            cout << (pos != -1 ? "DELETED" : "NOT FOUND") << "\n";
        }
    }
    return 0;
}
