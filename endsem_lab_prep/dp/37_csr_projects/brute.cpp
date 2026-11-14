// Brute force for 37: try all 3^n plans (0 = nothing, 1 = low, 2 = high), keep the valid ones
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> l(n), h(n);
    for (int i = 0; i < n; i++) cin >> l[i];
    for (int i = 0; i < n; i++) cin >> h[i];
    int total = 1;
    for (int i = 0; i < n; i++) total *= 3;
    long long best = 0;
    vector<int> plan(n);
    for (int code = 0; code < total; code++) {
        int c = code;
        for (int i = 0; i < n; i++) { plan[i] = c % 3; c /= 3; }
        bool ok = true;
        long long value = 0;
        for (int i = 0; i < n; i++) {
            if (plan[i] == 2 && i > 0 && plan[i - 1] != 0) ok = false;   // high needs an empty week before
            value += plan[i] == 1 ? l[i] : plan[i] == 2 ? h[i] : 0;
        }
        if (ok && value > best) best = value;
    }
    cout << best << "\n";
    return 0;
}
