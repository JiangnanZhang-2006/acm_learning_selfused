#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int> > v(n - 1, vector<int>(n - 1));
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            cin >> v[i][j];
        }
    }
    bool have = false;
    for (int a = 0; a < n - 1; a++) {
        for (int b = a + 2; b < n; b++) {
            for (int m = a + 1; m < b; m++) {
                if (v[a][m - a - 1] + v[m][b - m - 1] <  v[a][b - a - 1]) {
                    have = true;
                    break;
                }
            }
            if (have) break;
        }
        if (have) break;
    }
    cout << (have ? "Yes" : "No") << endl;
    return 0;
}