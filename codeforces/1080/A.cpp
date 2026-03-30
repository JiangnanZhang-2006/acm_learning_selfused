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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        bool have_67 = false;
        for (int i = 0; i < n; i++) {
            if (a[i] == 67) have_67 = true;
        }
        cout << (have_67 ? "YES" : "NO") << '\n';
    }

    return 0;
}