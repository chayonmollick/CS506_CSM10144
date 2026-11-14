// Brute: try every order of joins (exponential, N <= 7).
#include <iostream>
#include <vector>
using namespace std;
long long best(vector<long long> v) {
    if (v.size() <= 1) return 0;
    long long res = -1;
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = i + 1; j < v.size(); j++) {
            vector<long long> w;
            for (size_t k = 0; k < v.size(); k++) if (k != i && k != j) w.push_back(v[k]);
            w.push_back(v[i] + v[j]);
            long long c = v[i] + v[j] + best(w);
            if (res < 0 || c < res) res = c;
        }
    return res;
}
int main() {
    int n; cin >> n; vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cout << best(v) << "\n";
    return 0;
}
