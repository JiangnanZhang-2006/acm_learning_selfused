#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(3 * n);
        for (int i = 0; i < n; i++) {
            v[3 * i] = i + 1;
            v[3 * i + 1] = 3 * n - i * 2 - 1;
            v[3 * i + 2] = 3 * n - i * 2;
        }
        bool first = true;
        for (int i = 0; i < 3 * n; i++) {
            if (first) {
                cout << v[i];
                first = false;
            }
            else {
                cout << " " << v[i];
            }
        }
        cout << endl;
    }

    return 0;
}