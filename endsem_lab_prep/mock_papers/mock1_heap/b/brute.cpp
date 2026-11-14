// Brute force for Mock 1 (b): sort the prefix each time and take the lower median.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n; cin >> n; vector<int> v;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; v.push_back(x);
        vector<int> s = v; sort(s.begin(), s.end());
        cout << s[(s.size() - 1) / 2] << (i == n - 1 ? '\n' : ' ');
    }
}
