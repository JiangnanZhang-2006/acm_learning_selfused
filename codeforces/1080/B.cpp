#include <bits/stdc++.h>

using namespace std;

int odd_part(int x) {
    while (x % 2 == 0) x /= 2;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        bool valid = true;
        for (int i = 1; i <= n; i++) {
            if (odd_part(a[i]) != odd_part(i)) {
                valid = false;
                break;
            }
        }
        cout << (valid ? "YES" : "NO") << endl;
    }

    return 0;
}
