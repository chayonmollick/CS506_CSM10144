// 03. Two Sum: indices i < j with a[i] + a[j] = target (smallest j, then smallest i)
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long target;
    cin >> target;
    unordered_map<long long, int> first;          // value -> first index where it appeared
    for (int j = 0; j < n; j++) {
        unordered_map<long long, int>::iterator it = first.find(target - a[j]);
        if (it != first.end()) {                  // complement seen earlier: answer found
            cout << it->second << " " << j << "\n";
            return 0;
        }
        if (first.find(a[j]) == first.end()) first[a[j]] = j;   // keep the FIRST index only
    }
    cout << "-1 -1\n";
    return 0;
}
