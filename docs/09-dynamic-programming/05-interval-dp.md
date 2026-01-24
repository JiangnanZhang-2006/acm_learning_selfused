# 区间 DP

区间 DP 解决与区间相关的 DP 问题，通常涉及合并或分割区间。

## 矩阵链乘法

```cpp
// 问题：给定矩阵链，求最优的乘法顺序（最少乘法次数）
// 状态：dp[i][j] 表示矩阵链 A[i]...A[j] 的最少乘法次数
// 转移：dp[i][j] = min(dp[i][k] + dp[k+1][j] + p[i]*p[k+1]*p[j+1])
//       其中 k 是分割点，p 是矩阵维度数组
// 初始：dp[i][i] = 0

int matrixChainOrder(vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // len 是区间长度
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n-1];
}
```

## 常见应用

- 回文串相关问题
- 石子合并问题
- 括号匹配问题
- 区间染色问题

## 基本模式

```cpp
// 区间 DP 的基本模式
for (int len = 2; len <= n; len++) {        // 枚举区间长度
    for (int i = 0; i <= n - len; i++) {    // 枚举区间起点
        int j = i + len - 1;                 // 区间终点
        for (int k = i; k < j; k++) {       // 枚举分割点
            // 状态转移
            dp[i][j] = min/max(dp[i][j], dp[i][k] + dp[k+1][j] + cost);
        }
    }
}
```

## 优化

区间 DP 可以使用四边形不等式优化，将复杂度从 O(n³) 降低到 O(n²)。
