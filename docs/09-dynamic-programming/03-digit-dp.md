# 数位 DP

数位 DP 用于统计满足特定条件的数字个数，通常处理与数字每一位相关的问题。

## 思路分析

### 核心思想

数位 DP 的核心是将区间 `[L, R]` 的问题转化为 `[0, R]` 的问题，然后通过数位逐位处理。

### 区间划分策略

当处理区间 `[1, N]` 时，可以根据数字的位数和上界约束将区间划分为不同的段：

**示例：将区间 1 到 5926 划分为：**

```text
完整段（不受上界限制）：
1~9         1,2,...,9           完整段（1位数）
10~99       10,11,...,99         完整段（2位数）
100~999     100,101,...,999      完整段（3位数）

受限段（受上界限制，需要逐位处理）：
1000~4999   1xxx,2xxx,3xxx,4xxx  受限段（4位数，首位1-4）
5000~5899   50xx,51xx,...,58xx   受限段（前两位50-58）
5900~5919   590x,591x            受限段（前三位590-591）
5920~5925   5920,5921,...,5925   受限段（前四位5920-5925）
```

**划分原则：**

- **完整段**：该段内所有数字都不受上界限制，可以自由选择每一位
- **受限段**：该段内数字受到上界限制，需要根据上界逐位确定范围

### 状态定义

数位 DP 的状态通常包括：

1. **位置（pos）**：当前处理的数位位置（从高位到低位）
2. **状态（state）**：根据具体问题定义的状态（如数字和、数字特征等）
3. **限制（limit）**：当前已填数字是否等于上界的前缀
4. **前导零（lead）**：是否还在前导零阶段

### 状态转移

对于每一位，我们需要枚举所有可能的选择（0-9），但要注意：

- **limit = true**：当前位只能选择 `[0, digit[pos]]`
- **limit = false**：当前位可以选择 `[0, 9]`
- **lead = true**：当前还在前导零阶段，0 的选择需要特殊处理

**状态转移方程（伪代码）：**

```text
dp[pos][state][limit][lead] = 
    for i in [0, up]:  // up = limit ? digit[pos] : 9
        new_limit = limit && (i == up)
        new_lead = lead && (i == 0)
        new_state = updateState(state, i, new_lead)
        res += dp[pos-1][new_state][new_limit][new_lead]
```

### 记忆化优化

只有当 `!limit && !lead` 时，状态才是"通用"的，可以记忆化：

- **limit = true**：状态依赖于具体的上界，不能复用
- **lead = true**：前导零阶段的状态与正常状态不同，不能复用

## 基本模板

```cpp
// 问题：统计 [L, R] 区间内满足条件的数字个数
// 状态：dp[pos][state][limit][lead] 
//       - pos: 当前处理的数位位置
//       - state: 当前状态（根据具体问题定义）
//       - limit: 是否受到上界限制
//       - lead: 是否有前导零

int digit[20];
int dp[20][state_size][2][2];

int dfs(int pos, int state, bool limit, bool lead) {
    if (pos == -1) {
        return check(state);  // 检查状态是否满足条件
    }
    
    if (!limit && !lead && dp[pos][state][limit][lead] != -1) {
        return dp[pos][state][limit][lead];
    }
    
    int res = 0;
    int up = limit ? digit[pos] : 9;
    
    for (int i = 0; i <= up; i++) {
        bool new_limit = limit && (i == up);
        bool new_lead = lead && (i == 0);
        int new_state = updateState(state, i, new_lead);
        res += dfs(pos - 1, new_state, new_limit, new_lead);
    }
    
    if (!limit && !lead) {
        dp[pos][state][limit][lead] = res;
    }
    return res;
}

int solve(int x) {
    int len = 0;
    while (x) {
        digit[len++] = x % 10;
        x /= 10;
    }
    memset(dp, -1, sizeof(dp));
    return dfs(len - 1, 0, true, true);
}
```

## 关键点

1. **limit（上界限制）**：当前已填数字是否等于上界的前缀
2. **lead（前导零）**：是否还在前导零阶段
3. **state（状态）**：根据具体问题定义，如数字和、数字特征等
4. **记忆化条件**：只有在 `!limit && !lead` 时才能记忆化

## 常见应用

- 统计区间内不含某个数字的数字个数
- 统计区间内数字和为特定值的数字个数
- 统计区间内满足特定数字模式的数字个数
