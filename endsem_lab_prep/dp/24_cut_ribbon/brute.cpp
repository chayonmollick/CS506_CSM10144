// Brute force for 24: try every count i of a-pieces and j of b-pieces; the rest must be c-pieces
#include <iostream>
using namespace std;

int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int best = -1;
    for (int i = 0; i * a <= n; i++)
        for (int j = 0; i * a + j * b <= n; j++) {
            int rest = n - i * a - j * b;
            if (rest % c == 0 && i + j + rest / c > best) best = i + j + rest / c;
        }
    cout << best << "\n";
    return 0;
}
