// Brute force for 21: count step sequences by plain recursion (exponential, small n only)
#include <iostream>
using namespace std;

long long countWays(int n, int maxStep) {
    if (n == 0) return 1;
    long long total = 0;
    for (int s = 1; s <= maxStep && s <= n; s++) total += countWays(n - s, maxStep);
    return total;
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << countWays(n, 2) % 1000000007LL << "\n" << countWays(n, k) % 1000000007LL << "\n";
    return 0;
}
