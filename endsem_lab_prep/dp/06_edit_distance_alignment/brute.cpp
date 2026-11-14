// Brute force for 06: ALIGN-REC without memoization — tries every alignment (|X|, |Y| <= 7).
// Prints the minimum cost and one optimal alignment.
#include <iostream>
#include <string>
using namespace std;

string X, Y;
int delta, alpha;

int rec(int i, int j, string &top, string &bot) {  // align X[0..i) with Y[0..j)
    if (i == 0 || j == 0) {                          // the rest is gaps
        top = X.substr(0, i) + string(j, '-');
        bot = string(i, '-') + Y.substr(0, j);
        return (i + j) * delta;
    }
    string t1, b1, t2, b2, t3, b3;
    int c1 = rec(i - 1, j - 1, t1, b1) + (X[i - 1] == Y[j - 1] ? 0 : alpha);
    int c2 = rec(i - 1, j, t2, b2) + delta;
    int c3 = rec(i, j - 1, t3, b3) + delta;
    int best = c1;
    top = t1 + X[i - 1]; bot = b1 + Y[j - 1];
    if (c2 < best) { best = c2; top = t2 + X[i - 1]; bot = b2 + '-'; }
    if (c3 < best) { best = c3; top = t3 + '-'; bot = b3 + Y[j - 1]; }
    return best;
}

int main() {
    cin >> X >> Y >> delta >> alpha;
    string top, bot;
    int c = rec((int)X.size(), (int)Y.size(), top, bot);
    cout << c << "\n" << top << "\n" << bot << "\n";
    return 0;
}
