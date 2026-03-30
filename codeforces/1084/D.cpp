#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        int Lm = y - x;

        int mn = v[x], mnpos = x;
        for (int i = x + 1; i < y; i++)
            if (v[i] < mn) { mn = v[i]; mnpos = i; }

        vector<int> C;
        for (int i = 0; i < x; i++) C.push_back(v[i]);
        for (int i = y; i < n; i++) C.push_back(v[i]);

        int s = 0;
        while (s < (int)C.size() && C[s] < mn) s++;

        vector<int> res;
        for (int i = 0; i < s; i++) res.push_back(C[i]);
        for (int i = 0; i < Lm; i++) res.push_back(v[x + (mnpos - x + i) % Lm]);
        for (int i = s; i < (int)C.size(); i++) res.push_back(C[i]);

        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}
