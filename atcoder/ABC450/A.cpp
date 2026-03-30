#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    n++;
    bool first = true;
    while (--n) {
        if (first) {
            cout << n;
            first = false;
        }
        else {
            cout << ',' << n;
        }
    }
    cout << endl;
    return 0;
}