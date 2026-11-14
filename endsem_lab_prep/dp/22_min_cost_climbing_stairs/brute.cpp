// Brute force for 22: try every sequence of 1/2-steps from step 0 and from step 1
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> cost;

long long best(int i) {               // cheapest way from step i to the top, trying both moves
    if (i >= n) return i == n ? 0 : (long long)4e18;   // overshooting the top is not allowed
    long long a = best(i + 1), b = best(i + 2);
    return cost[i] + (a < b ? a : b);
}

int main() {
    cin >> n;
    cost.resize(n);
    for (int i = 0; i < n; i++) cin >> cost[i];
    long long a = best(0), b = (n >= 1 ? best(1) : 0);
    cout << (a < b ? a : b) << "\n";
    return 0;
}
