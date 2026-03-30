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
        string s;
        cin >> s;
        string ans = "";
        for (int i = 0; i < n; i++) {
            ans += "*";
        }
        string prev = ans;
        while (s != prev && s != ans) {
            prev = s;
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (s[i] == '*') break;
                    if (s[j] == '*') continue;
                    if (s[i] == s[j]) {
                        s[i] = '*';
                        s[j] = '*';
                    }
                    break;
                }
            }
        }
        cout << (s == ans ? "YES" : "NO") << endl;
    }

    return 0;
}