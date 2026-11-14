// 15. Slots from the division, multiplication (Knuth A) and universal hash functions
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long m, p, a, b;
    int n;
    cin >> m >> n;
    vector<long long> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];
    cin >> p >> a >> b;
    const double A = (sqrt(5.0) - 1) / 2;           // 0.6180339887...
    cout << "Division:";                            // h(k) = k mod m
    for (int i = 0; i < n; i++) cout << " " << ((k[i] % m) + m) % m;
    cout << "\nMultiplication:";                    // h(k) = floor(m * (k*A mod 1))
    for (int i = 0; i < n; i++) {
        double x = k[i] * A;
        double frac = x - floor(x);                 // fractional part of k*A
        cout << " " << (long long)floor(m * frac);
    }
    cout << "\nUniversal:";                         // h(k) = ((a*k + b) mod p) mod m
    for (int i = 0; i < n; i++) cout << " " << ((a * k[i] + b) % p) % m;
    cout << "\n";
    return 0;
}
