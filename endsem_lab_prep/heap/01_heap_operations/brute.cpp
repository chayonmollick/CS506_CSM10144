// Brute: unsorted vector, minimum by linear scan.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<long long> v;
    int q;
    cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op == "insert") { long long x; cin >> x; v.push_back(x); }
        else if (op == "size") cout << v.size() << "\n";
        else if (v.empty()) cout << "EMPTY\n";
        else {
            vector<long long>::iterator it = min_element(v.begin(), v.end());
            cout << *it << "\n";
            if (op == "removeMin") v.erase(it);
        }
    }
    sort(v.begin(), v.end());
    if (v.empty()) cout << "EMPTY\n";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 < v.size() ? " " : "\n");
    return 0;
}
