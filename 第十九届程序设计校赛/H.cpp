// H：下一个有重复的组合（r-可重组合字典序后继）
// pref[k]=a[0]+…+a[k-1]（pref[0]=0）。a[i+1]+…+a[n-1] = r - pref[i+1]。
// 找最大的 i（0<=i<=n-2）使得 r - pref[i+1] > 0，则 a[i]++，
// a[i+1..n-2]=0，a[n-1] = (r - pref[i+1]) - 1。

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, r;
        cin >> n >> r;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<long long> pref(n + 1);
        pref[0] = 0;
        for (int j = 0; j < n; j++) pref[j + 1] = pref[j] + a[j];

        for (int i = n - 2; i >= 0; i--) {
            long long right = r - pref[i + 1];  // sum a[i+1..n-1]
            if (right > 0) {
                long long rest = right - 1;
                a[i]++;
                for (int j = i + 1; j < n - 1; j++) a[j] = 0;
                a[n - 1] = static_cast<int>(rest);
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
