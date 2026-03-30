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
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<array<int, 7>> dp(n + 1);
        for (int v = 1; v <= 6; v++) dp[1][v] = (a[1] != v);
        for (int i = 2; i <= n; i++) {
            for (int v = 1; v <= 6; v++) {
                dp[i][v] = INT_MAX;
                for (int u = 1; u <= 6; u++) {
                    if (u != v && u + v != 7) dp[i][v] = min(dp[i][v], dp[i - 1][u] + (a[i] != v));
                }
            }
        }
        int ans = INT_MAX;
        for (int v = 1; v <= 6; v++) ans = min(ans, dp[n][v]);
        cout << ans << '\n';
    }

    return 0;
}
