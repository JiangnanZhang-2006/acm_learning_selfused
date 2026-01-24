# 动态规划基础

## 基本概念

动态规划（Dynamic Programming，简称 DP）是一种通过把原问题分解为相对简单的子问题的方式来解决复杂问题的方法。

### 核心思想

1. **最优子结构**：问题的最优解包含子问题的最优解
2. **重叠子问题**：在递归过程中，同一个子问题会被多次计算
3. **状态转移**：通过状态转移方程描述子问题之间的关系

### 基本步骤

1. **定义状态**：`dp[i]` 或 `dp[i][j]` 表示什么
2. **状态转移方程**：如何从已知状态推导出当前状态
3. **初始状态**：边界条件的设置
4. **计算顺序**：确定状态的计算顺序

## 一维动态规划

### 经典问题：斐波那契数列

```cpp
// 问题：求第 n 个斐波那契数
// F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)

// 方法1：递归（效率低，会重复计算）
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// 方法2：记忆化搜索
int memo[100] = {0};  // 初始化为 0，0 表示未计算（注意：memo[0]=0 是有效值，但已在 n<=1 时处理）
int fib_memo(int n) {
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];  // 已计算过，直接返回
    return memo[n] = fib_memo(n-1) + fib_memo(n-2);
}

// 方法3：动态规划（自底向上）
int fib_dp(int n) {
    if (n <= 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// 方法4：空间优化（只保留前两个状态）
int fib_optimized(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

### 爬楼梯问题

```cpp
// 问题：每次可以爬 1 或 2 个台阶，到达第 n 阶有多少种方法
// 状态：dp[i] 表示到达第 i 阶的方法数
// 转移：dp[i] = dp[i-1] + dp[i-2]
// 初始：dp[0] = 1, dp[1] = 1

int climbStairs(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
```

### 最大子数组和

```cpp
// 问题：找到数组中和最大的连续子数组
// 状态：dp[i] 表示以第 i 个元素结尾的最大子数组和
// 转移：dp[i] = max(nums[i], dp[i-1] + nums[i])
// 初始：dp[0] = nums[0]

int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];
    int maxSum = dp[0];
    
    for (int i = 1; i < n; i++) {
        dp[i] = max(nums[i], dp[i-1] + nums[i]);
        maxSum = max(maxSum, dp[i]);
    }
    return maxSum;
}

// 空间优化版本
int maxSubArray_optimized(vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
```

## 二维动态规划

### 最长公共子序列 (LCS)

```cpp
// 问题：求两个字符串的最长公共子序列长度
// 状态：dp[i][j] 表示 s1[0..i-1] 和 s2[0..j-1] 的 LCS 长度
// 转移：
//   - 如果 s1[i-1] == s2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
//   - 否则: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// 初始：dp[0][j] = 0, dp[i][0] = 0

int longestCommonSubsequence(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}
```

### 编辑距离

```cpp
// 问题：将字符串 s1 转换为 s2 所需的最少操作数（插入、删除、替换）
// 状态：dp[i][j] 表示 s1[0..i-1] 转换为 s2[0..j-1] 的最少操作数
// 转移：
//   - 如果 s1[i-1] == s2[j-1]: dp[i][j] = dp[i-1][j-1]
//   - 否则: dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
// 初始：dp[i][0] = i, dp[0][j] = j

int editDistance(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // 初始化
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
            }
        }
    }
    return dp[m][n];
}
```
