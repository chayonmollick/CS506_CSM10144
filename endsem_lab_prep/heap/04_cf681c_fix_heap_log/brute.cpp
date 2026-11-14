// Brute: same rules, heap replaced by a sorted vector (O(n^2)).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
int main() {
    int n; cin >> n;
    vector<long long> h;   // kept sorted ascending
    ostringstream os; int cnt = 0;
    for (int k = 0; k < n; k++) {
        string op; cin >> op;
        if (op == "insert") { long long x; cin >> x; h.insert(upper_bound(h.begin(), h.end(), x), x);
            os << "insert " << x << "\n"; cnt++; }
        else if (op == "removeMin") { if (h.empty()) { h.push_back(0); os << "insert 0\n"; cnt++; }
            h.erase(h.begin()); os << "removeMin\n"; cnt++; }
        else { long long x; cin >> x;
            while (!h.empty() && h[0] < x) { h.erase(h.begin()); os << "removeMin\n"; cnt++; }
            if (h.empty() || h[0] > x) { h.insert(h.begin(), x); os << "insert " << x << "\n"; cnt++; }
            os << "getMin " << x << "\n"; cnt++; }
    }
    cout << cnt << "\n" << os.str();
    return 0;
}
