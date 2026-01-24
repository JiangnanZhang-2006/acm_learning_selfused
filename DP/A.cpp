#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAXL = 30;

long long dp[MAXL][2];      // dp[i][0] 表示长度为i的数字中包含49的数字个数，dp[i][1] 表示长度为i的数字中不包含49且开头为9的数字个数
long long pow10[MAXL];

void create_dp() {
    dp[0][0] = 0;
    dp[0][1] = 0;
    pow10[0] = 1;
    for (int i = 1; i < MAXL; i++) {
        pow10[i] = pow10[i - 1] * 10LL;
    }
    for (int i = 1; i < MAXL; i++) {
        dp[i][0] = dp[i - 1][0] * 10 + dp[i - 1][1];
        dp[i][1] = pow10[i - 1] - dp[i - 1][0];
    }
}

int main() {
    int n;
    cin >> n;
    create_dp();
    while (n--) {
        long long r;
        cin >> r;
        long long ans = 0;
        int len = static_cast<int>(log10(r) + 1);
        vector<int> digits;
        while (r) {
            digits.push_back(static_cast<int>(r % 10));
            r /= 10;
        }
        bool have49 = false;
        int prev = 0;
        for (int i = len - 1; i >= 0; i--) {

            int curr = digits[i];

            for (int j = 0; j < curr; j++) {
                if (have49) {
                    ans += pow10[i];
                } else {
                    if (j == 9 && prev == 4) {
                        ans += pow10[i];
                    } else if (j == 4) {
                        ans += dp[i][1] + dp[i][0];
                    } else {
                        ans += dp[i][0];
                    }
                }
            }

            if (curr == 9 && prev == 4) {
                have49 = true;
            }
            prev = curr;
            
        }
        if (have49) {
            ans ++;
        }
        cout << ans << endl;
    }
    return 0;
}