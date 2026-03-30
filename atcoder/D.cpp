#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> R(N);
        for (int i = 0; i < N; i++) {
            cin >> R[i];
        }

        vector<int> f(N), g(N);
        f[0] = R[0];
        for (int i = 1; i < N; i++) {
            f[i] = min(R[i], f[i-1] + 1);
        }

        g[N-1] = R[N-1];
        for (int i = N-2; i >= 0; i--) {
            g[i] = min(R[i], g[i+1] + 1);
        }

        long long ans = 0;
        for (int i = 0; i < N; i++) {
            int x = min(f[i], g[i]);
            ans += R[i] - x;
        }

        cout << ans << endl;
    }

    return 0;
}