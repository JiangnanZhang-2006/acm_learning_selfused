# 数位DP问题总结：不吉利数字统计

## 问题描述

统计区间 `[l, r]` 内包含数字4或连续数字62的"不吉利"数字个数。

**输入格式**：每行两个整数 `l r`，当 `l + r = 0` 时结束。

**输出格式**：每行输出区间 `[l, r]` 内吉利数字的个数（总数 - 不吉利数字）。

---

## 原始代码的问题分析

### 问题1：DP转移方程中的重复计算

**错误代码：**

```cpp
dp[i][0] = dp[i - 1][0] * 9 + dp[i - 1][1] + pow10[i - 1];
```

**问题分析：**

`dp[i][1]` 表示"长度为i，不含4和62，且最高位是2"的数字个数。

当从长度i-1扩展到i时，在高位添加数字：

- 添加0,1,2,3,5,7,8,9（8种）：只有已经不吉利的还是不吉利
- **添加4**：所有i-1位数都变不吉利 → `pow10[i-1]`（包含了`dp[i-1][1]`）
- **添加6**：已经不吉利的 + 最高位是2的（形成62）→ `dp[i-1][0] + dp[i-1][1]`

在这个公式中，`dp[i-1][1]` 被计算了**两次**：

1. 在 `pow10[i-1]` 中（添加4时）
2. 在 `+ dp[i-1][1]` 中（添加6时）

**正确的公式：**

```cpp
dp[i][0] = dp[i - 1][0] * 9 + pow10[i - 1];
```

---

### 问题2：digits数组索引顺序错误

**错误代码：**

```cpp
vector<int> digits(len);
for (int i = len - 1; i >= 0; --i) {
    digits[i] = n % 10;
    n /= 10;
}
```

**问题：**

- 这样会让 `digits[0]` 存储高位，`digits[len-1]` 存储低位
- 但后续循环中使用 `digits[i]` 时，`i` 是从高位到低位递减的
- 导致数字顺序完全反了

**正确做法：**

```cpp
for (int i = 0; i < len; ++i) {
    digits[i] = n % 10;
    n /= 10;
}
// 现在 digits[0] 是低位，digits[len-1] 是高位
// 循环时从 len-1 到 0，正确对应高位到低位
```

---

### 问题3：前导0处理不当

**核心问题：**

对于三位数 `100`，当枚举百位填0时：

- 实际表示的是 `[0, 99]`
- 这包括1位数 `[0, 9]` 和2位数 `[10, 99]`
- `dp[2][0] = 19` 只统计了 `[10, 99]` 中的不吉利数
- **遗漏了1位数中的不吉利数**

迭代式数位DP处理前导0需要额外的累加逻辑，非常容易出错。

---

### 问题4：区间边界处理

**错误代码：**

```cpp
cout << solve(r) - solve(l) << endl;
```

这计算的是 `(l, r]` 区间（不包含l）。

**正确代码：**

```cpp
cout << solve(r) - solve(l - 1) << endl;
```

计算 `[l, r]` 区间（包含l）。

---

## 两种数位DP实现方式对比

### 方法1：迭代式DP（原始方法）

**思路：**

1. 预处理：`dp[i][j]` 表示长度为i、某种状态j的数字个数
2. 从高到低枚举每一位，累加答案

**优点：**

- 预处理后查询快

**缺点：**

- DP状态定义和转移复杂
- 前导0处理困难
- 容易出错，调试困难
- 需要精确设计DP维度

---

### 方法2：记忆化搜索（推荐）

**思路：**

```cpp
long long dfs(int pos, bool is_unlucky, bool prev_is_6, bool limit)
```

- `pos`: 当前处理的位（从高到低）
- `is_unlucky`: 前面是否已经包含4或62
- `prev_is_6`: 前一位是否是6
- `limit`: 是否受到原数字的限制

**优点：**

- 状态转移清晰直观
- 自动处理前导0（limit标志）
- 容易扩展和修改
- 调试友好

**完整代码：**

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int digits[20];
long long dp[20][2][2];  // dp[pos][is_unlucky][prev_is_6]
bool vis[20][2][2];

long long dfs(int pos, bool is_unlucky, bool prev_is_6, bool limit) {
    // 边界：所有位都处理完
    if (pos == -1) {
        return is_unlucky ? 1 : 0;
    }
    
    // 记忆化：如果没有limit限制且已经计算过，直接返回
    if (!limit && vis[pos][is_unlucky][prev_is_6]) {
        return dp[pos][is_unlucky][prev_is_6];
    }
    
    // 确定当前位可以填的最大数字
    int up = limit ? digits[pos] : 9;
    long long ans = 0;
    
    // 枚举当前位填0-up
    for (int i = 0; i <= up; i++) {
        bool new_unlucky = is_unlucky || (i == 4) || (prev_is_6 && i == 2);
        bool new_prev_is_6 = (i == 6);
        ans += dfs(pos - 1, new_unlucky, new_prev_is_6, limit && (i == up));
    }
    
    // 保存结果（只保存无limit限制的情况）
    if (!limit) {
        vis[pos][is_unlucky][prev_is_6] = true;
        dp[pos][is_unlucky][prev_is_6] = ans;
    }
    
    return ans;
}

long long solve(long long n) {
    if (n <= 0) return 0;
    
    // 提取数字的每一位
    int len = 0;
    while (n) {
        digits[len++] = n % 10;
        n /= 10;
    }
    
    // 清空记忆化数组
    memset(vis, false, sizeof(vis));
    
    // 从最高位开始搜索
    return dfs(len - 1, false, false, true);
}

int main() {
    long long l, r;
    while (cin >> l >> r && (l + r)) {
        long long unlucky = solve(r) - solve(l - 1);
        long long total = r - l + 1;
        cout << total - unlucky << endl;  // 吉利数字个数
    }
    return 0;
}
```

---

## 核心知识点总结

### 1. 数位DP的本质

数位DP是一种**按位枚举**的计数问题，核心在于：

- 从高位到低位依次确定每一位
- 维护必要的状态信息
- 用记忆化避免重复计算

### 2. limit标志的作用

`limit` 表示当前是否受到原数字的限制：

- `limit = true`：当前位最大只能填 `digits[pos]`
- `limit = false`：当前位可以填 `0-9` 任意数字

**为什么需要limit？**

计算 `[0, 523]` 时：

- 百位填5，十位最多填2（受限制）
- 百位填4，十位可以填0-9（不受限制）

### 3. 记忆化的条件

只有 `!limit` 时才能记忆化，因为：

- 有limit时，结果依赖于具体的上界
- 无limit时，状态与上界无关，可以复用

### 4. 前导0的处理

在记忆化搜索中，**前导0自动被正确处理**：

- 枚举时包含了从0开始的所有情况
- 状态转移天然包含了"数字位数减少"的情况

### 5. 常见错误

1. **DP转移重复计算**：仔细分析每个状态被加了几次
2. **数组索引错误**：明确高位和低位的存储顺序
3. **边界条件**：`[l, r]` 应该用 `solve(r) - solve(l - 1)`
4. **状态定义不完整**：确保状态能够完全刻画子问题

---

## 练习建议

1. **理解记忆化搜索模板**
   - 状态定义：位置 + 必要的限制信息
   - 边界条件：所有位处理完
   - 记忆化条件：!limit

2. **手动模拟小数据**
   - 用 `[1, 10]` 等小数据手动跟踪DFS过程
   - 验证每一步的状态转移

3. **类似题目**
   - 统计不含某些数字的数
   - 统计各位数字和为k的倍数的数
   - 统计回文数
   - 统计windy数（相邻数字差≥2）

---

## 总结

- **迭代式数位DP**：需要精心设计状态，容易出错，不推荐初学者使用
- **记忆化搜索**：模板清晰，易于理解和扩展，强烈推荐
- **关键点**：状态定义、limit标志、记忆化条件、边界处理

记住：**数位DP就是按位枚举 + 记忆化搜索**。先掌握记忆化搜索模板，再根据具体问题调整状态定义。
