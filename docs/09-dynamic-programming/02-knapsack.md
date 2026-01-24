# 背包问题

背包问题是一类经典的动态规划问题，根据物品的选择限制不同，可以分为以下几种类型。

## 0-1 背包

每个物品只能选择一次或不选。

```cpp
// 问题：有 n 个物品，每个物品有重量 w[i] 和价值 v[i]，背包容量为 W
//       每个物品只能选一次，求最大价值
// 状态：dp[i][j] 表示前 i 个物品，容量为 j 时的最大价值
// 转移：
//   - 不选第 i 个物品: dp[i][j] = dp[i-1][j]
//   - 选第 i 个物品: dp[i][j] = dp[i-1][j-w[i]] + v[i]
//   - dp[i][j] = max(不选, 选)
// 初始：dp[0][j] = 0

int knapsack01(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i-1][j];  // 不选
            if (j >= w[i-1]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-w[i-1]] + v[i-1]);
            }
        }
    }
    return dp[n][W];
}

// 空间优化（一维数组，逆序更新）
int knapsack01_optimized(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = W; j >= w[i]; j--) {  // 逆序更新
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

## 完全背包

每个物品可以选择无限次。

```cpp
// 问题：每个物品可以选择无限次
// 状态：dp[i][j] 表示前 i 个物品，容量为 j 时的最大价值
// 转移：dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i])
//       注意：选第 i 个物品时，状态来自 dp[i][j-w[i]]（可以继续选）

int knapsackComplete(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = w[i]; j <= W; j++) {  // 正序更新
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

## 多重背包

每个物品最多可以选择 `c[i]` 次。

```cpp
// 问题：每个物品最多可以选择 c[i] 次
// 方法：转化为 0-1 背包（二进制优化）

int knapsackMultiple(vector<int>& w, vector<int>& v, vector<int>& c, int W) {
    int n = w.size();
    vector<int> new_w, new_v;
    
    // 二进制拆分
    for (int i = 0; i < n; i++) {
        int cnt = c[i];
        for (int k = 1; k <= cnt; k *= 2) {
            new_w.push_back(w[i] * k);
            new_v.push_back(v[i] * k);
            cnt -= k;
        }
        if (cnt > 0) {
            new_w.push_back(w[i] * cnt);
            new_v.push_back(v[i] * cnt);
        }
    }
    
    // 转化为 0-1 背包
    return knapsack01_optimized(new_w, new_v, W);
}
```
