// Brute force for 08: try lengths from long to short, compare every pair of windows.
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = (int)s.size();
    for (int L = n - 1; L >= 1; L--)
        for (int j = 0; j + L <= n; j++)
            for (int i = j + 1; i + L <= n; i++)
                if (s.compare(j, L, s, i, L) == 0) {
                    cout << L << "\n" << s.substr(j, L) << "\n";
                    return 0;
                }
    cout << 0 << "\n";
    return 0;
}
