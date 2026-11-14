// Brute force for the open-addressing template: builds each key's whole probe sequence
// first (incrementally, not from the closed formula), keeps a separate state array.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int m;
string w;
long long c1, c2;

long long pmod(long long a, long long b) { long long r = a % b; return r < 0 ? r + b : r; }

vector<int> sequence(long long k) {
    vector<int> seq;
    long long pos = pmod(k, m);
    long long step = (m > 1) ? 1 + pmod(k, m - 1) : 1;
    for (long long i = 0; i < m; i++) {
        seq.push_back((int)pos);
        if (w == "LINEAR") pos = pmod(pos + 1, m);
        else if (w == "DOUBLE") pos = pmod(pos + step, m);
        else pos = pmod(pos + c1 + c2 * (2 * i + 1), m);  // difference of consecutive quadratic probes
    }
    return seq;
}

int main() {
    cin >> m >> w;
    if (w == "QUADRATIC") cin >> c1 >> c2;
    int q;
    cin >> q;
    vector<int> state(m, 0), key(m, 0);   // state: 0 empty, 1 used, 2 deleted
    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') {
            for (int j = 0; j < m; j++) {
                if (j) cout << " ";
                if (state[j] == 0) cout << "-";
                else if (state[j] == 2) cout << "D";
                else cout << key[j];
            }
            cout << "\n";
            continue;
        }
        int x;
        cin >> x;
        vector<int> seq = sequence(x);
        int found = -1, sp = 0;
        for (int i = 0; i < m; i++) {
            sp = i + 1;
            if (state[seq[i]] == 1 && key[seq[i]] == x) { found = seq[i]; break; }
            if (state[seq[i]] == 0) break;
        }
        if (op == 'S') {
            if (found >= 0) cout << "FOUND " << found << " probes " << sp << "\n";
            else cout << "NOT FOUND probes " << sp << "\n";
        } else if (op == 'D') {
            if (found >= 0) { state[found] = 2; cout << "DELETED " << found << "\n"; }
            else cout << "NOT FOUND\n";
        } else {
            if (found >= 0) { cout << "DUPLICATE\n"; continue; }
            int at = -1, p = 0;
            for (int i = 0; i < m && at < 0; i++)
                if (state[seq[i]] != 1) { at = seq[i]; p = i + 1; }
            if (at < 0) cout << "OVERFLOW\n";
            else { state[at] = 1; key[at] = x; cout << "slot " << at << " probes " << p << "\n"; }
        }
    }
    return 0;
}
