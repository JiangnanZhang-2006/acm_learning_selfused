#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        long long n, x, y;
        cin >> n >> x >> y;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long tot = 0;
        for (int i = 0; i < n; i++) {
            tot += (a[i] / x) * y;
        }
        long long res = 0;
        for (int i = 0; i < n; i++) {
            long long cur = a[i] + tot - (a[i] / x) * y;
            res = max(res, cur);
        }
        cout << res << endl;
    }
}