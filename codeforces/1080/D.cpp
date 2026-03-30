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
        vector<long long> f(n + 1);
        for (int i = 1; i <= n; i++) cin >> f[i];

        long long sum_n = (f[1] + f[n]) / (n - 1);

        vector<long long> pref(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            long long g = f[i + 1] - f[i];
            pref[i] = (sum_n + g) / 2;
        }

        cout << pref[1];
        for (int i = 2; i <= n - 1; i++) {
            cout << ' ' << (pref[i] - pref[i - 1]);
        }
        cout << ' ' << (sum_n - pref[n - 1]) << endl;
    }

    return 0;
}