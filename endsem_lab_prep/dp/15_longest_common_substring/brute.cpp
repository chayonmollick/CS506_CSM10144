// Brute force for 15: every substring of X (start left to right, longest first), test with find().
#include <iostream>
#include <string>
using namespace std;

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = X.size();
    string best;
    for (int st = 0; st < m; st++)
        for (int len = m - st; len > (int)best.size(); len--)
            if (Y.find(X.substr(st, len)) != string::npos) { best = X.substr(st, len); break; }
    cout << best.size() << "\n" << best << "\n";
    return 0;
}
