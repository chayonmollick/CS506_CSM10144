// Brute force for 26: try every buy/sell/skip decision with a transaction counter (exponential)
#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<long long> p;

long long go(int i, bool holding, int used) {     // used = transactions started so far
    if (i == n) return 0;
    long long best = go(i + 1, holding, used);     // do nothing today
    if (holding) {
        long long s = p[i] + go(i + 1, false, used);
        if (s > best) best = s;
    } else if (used < k) {
        long long b = -p[i] + go(i + 1, true, used + 1);
        if (b > best) best = b;
    }
    return best;
}

int main() {
    cin >> n >> k;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    cout << go(0, false, 0) << "\n";
    return 0;
}
