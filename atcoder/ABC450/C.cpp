#include <bits/stdc++.h>

using namespace std;

vector<vector<char> > input;
int n, m;

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return;
    if (input[x][y] == '#') return;
    input[x][y] = '#';
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    input.assign(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> input[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        dfs(i, 0);
        dfs(i, m - 1);
    }
    for (int j = 0; j < m; j++) {
        dfs(0, j);
        dfs(n - 1, j);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] == '.') {
                dfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}