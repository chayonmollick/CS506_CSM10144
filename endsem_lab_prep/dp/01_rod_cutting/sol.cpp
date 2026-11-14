// 01 Rod cutting: EXTENDED-BOTTOM-UP-CUT-ROD + PRINT-CUT-ROD-SOLUTION
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];

    vector<long long> r(n + 1, 0);  // r[j] = best revenue for a rod of length j
    vector<int> s(n + 1, 0);        // s[j] = size of the first piece in that best cut
    r[0] = 0;                       // base case: empty rod earns 0
    for (int j = 1; j <= n; j++) {
        long long q = -1;
        for (int i = 1; i <= j; i++) {
            if (p[i] + r[j - i] > q) {  // strict '>' keeps the smallest first piece on ties
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }

    cout << r[n] << "\n";
    // traceback: cut off s[j], continue with the rest of the rod
    bool first = true;
    for (int j = n; j > 0; j -= s[j]) {
        if (!first) cout << " ";
        cout << s[j];
        first = false;
    }
    cout << "\n";
    return 0;
}
