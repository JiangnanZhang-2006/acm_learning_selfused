#include <iostream>
#include <cstring>
using namespace std;

int digits[20];
long long dp[20][2][2];  // dp[pos][is_62_or_4][prev_is_6]
bool vis[20][2][2];

// dfs(pos, is_unlucky, prev_is_6, limit)
// returns count of unlucky numbers
long long dfs(int pos, bool is_unlucky, bool prev_is_6, bool limit) {
    if (pos == -1) {
        return is_unlucky ? 1 : 0;
    }
    
    if (!limit && vis[pos][is_unlucky][prev_is_6]) {
        return dp[pos][is_unlucky][prev_is_6];
    }
    
    int up = limit ? digits[pos] : 9;
    long long ans = 0;
    
    for (int i = 0; i <= up; i++) {
        bool new_unlucky = is_unlucky || (i == 4) || (prev_is_6 && i == 2);
        bool new_prev_is_6 = (i == 6);
        ans += dfs(pos - 1, new_unlucky, new_prev_is_6, limit && (i == up));
    }
    
    if (!limit) {
        vis[pos][is_unlucky][prev_is_6] = true;
        dp[pos][is_unlucky][prev_is_6] = ans;
    }
    
    return ans;
}

long long solve(long long n) {
    if (n <= 0) return 0;
    
    int len = 0;
    while (n) {
        digits[len++] = n % 10;
        n /= 10;
    }
    
    memset(vis, false, sizeof(vis));
    return dfs(len - 1, false, false, true);
}

int main() {
    long long l, r;
    while (cin >> l >> r && (l + r)) {
        cout << r - l + 1 - (solve(r) - solve(l - 1)) << endl;
    }
    return 0;
}
 