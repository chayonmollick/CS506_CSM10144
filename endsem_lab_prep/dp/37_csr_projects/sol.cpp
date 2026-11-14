// 37. CSR Projects: low-effort l[i] or high-effort h[i] (needs a free week before it), maximise value
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> l(n + 1), h(n + 1);
    for (int i = 1; i <= n; i++) cin >> l[i];
    for (int i = 1; i <= n; i++) cin >> h[i];
    // OPT(i) = max(OPT(i-1) + l[i], OPT(i-2) + h[i]); base OPT(-1) = OPT(0) = 0
    long long opt2 = 0, opt1 = 0;                  // OPT(i-2), OPT(i-1)
    for (int i = 1; i <= n; i++) {
        long long cur = max(opt1 + l[i], opt2 + h[i]);   // low in week i, or week i-1 free + high in week i
        opt2 = opt1;
        opt1 = cur;
    }
    cout << opt1 << "\n";
    return 0;
}
