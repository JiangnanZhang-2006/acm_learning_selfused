#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        vector<int> v(7);
        for (int i = 0; i < 7; i++) cin >> v[i];
        sort(v.begin(), v.end());
        cout << -v[0] - v[1] - v[2] - v[3] - v[4] - v[5] + v[6] << endl;
    }
}