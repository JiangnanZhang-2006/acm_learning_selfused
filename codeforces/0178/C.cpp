#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<string> s(k);
        for (int i = 0; i < k; i++) {
            cin >> s[i];
        }
        bool find = false;
        for (int l = 1; l <= n && !find; l++) {
            if (n % l != 0) continue;
            string t(l, '?');
            bool ok = true;
            for (int j = 0; j < l && ok; j++) {
                set<char> inter;
                for (int pos = j; pos < n; pos += l) {
                    set<char> at_pos;
                    for (int m = 0; m < k; m++) {
                        at_pos.insert(s[m][pos]);
                    }
                    if (inter.empty()) {
                        inter = at_pos;
                    } else {
                        set<char> nxt;
                        for (char c : inter) {
                            if (at_pos.count(c)) nxt.insert(c);
                        }
                        inter = std::move(nxt);
                        if (inter.empty()) break;
                    }
                }
                if (inter.empty()) {
                    ok = false;
                } else {
                    t[j] = *inter.begin();
                }
            }
            if (ok) {
                string res;
                for (int i = 0; i < n / l; i++) {
                    res += t;
                }
                cout << res << "\n";
                find = true;
            }
        }
    }
    return 0;
}