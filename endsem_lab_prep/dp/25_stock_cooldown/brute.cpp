// Brute force for 25: try every buy/sell/skip decision on every day (exponential)
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> p;

// best profit from day i on; holding = own a unit; canBuy = false on the day after a sale
long long go(int i, bool holding, bool canBuy) {
    if (i == n) return 0;                       // an unsold unit is simply worth nothing
    long long best = go(i + 1, holding, true);  // do nothing today
    if (holding) {
        long long s = p[i] + go(i + 1, false, false);
        if (s > best) best = s;
    } else if (canBuy) {
        long long b = -p[i] + go(i + 1, true, true);
        if (b > best) best = b;
    }
    return best;
}

int main() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    cout << go(0, false, true) << "\n";
    return 0;
}
