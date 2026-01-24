# 状压 DP

状压 DP（状态压缩动态规划）通过二进制或其他方式压缩状态，处理状态数量较少但状态转移复杂的 DP 问题。

## 旅行商问题 (TSP)

```cpp
// 问题：访问所有城市一次并回到起点，求最短路径
// 状态：dp[mask][i] 表示访问过 mask 中的城市，当前在城市 i 的最短路径
// 转移：dp[mask][i] = min(dp[mask^(1<<i)][j] + dist[j][i])
// 初始：dp[1<<0][0] = 0（从城市 0 开始）

int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    int total = 1 << n;
    vector<vector<int>> dp(total, vector<int>(n, INT_MAX));
    
    dp[1][0] = 0;  // 从城市 0 开始
    
    for (int mask = 1; mask < total; mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                int new_mask = mask | (1 << j);
                if (dp[mask][i] != INT_MAX) {
                    dp[new_mask][j] = min(dp[new_mask][j], 
                                          dp[mask][i] + dist[i][j]);
                }
            }
        }
    }
    
    // 回到起点
    int result = INT_MAX;
    for (int i = 1; i < n; i++) {
        if (dp[total-1][i] != INT_MAX) {
            result = min(result, dp[total-1][i] + dist[i][0]);
        }
    }
    return result;
}
```

## 常见应用

- 棋盘问题（如 N 皇后、棋盘覆盖）
- 集合覆盖问题
- 状态数较少的 DP 问题（通常 n ≤ 20）

## 技巧

1. **位运算操作**：
   - `mask & (1 << i)`：检查第 i 位是否为 1
   - `mask | (1 << i)`：将第 i 位设为 1
   - `mask ^ (1 << i)`：翻转第 i 位
   - `mask & (mask - 1)`：移除最低位的 1

2. **状态枚举**：
   - 枚举子集：`for (int sub = mask; sub; sub = (sub - 1) & mask)`
   - 枚举超集：通过补集操作
