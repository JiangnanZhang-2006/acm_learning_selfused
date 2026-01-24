# 动态规划优化技巧

## 滚动数组

当状态转移只依赖前一行或前几行时，可以用滚动数组减少空间复杂度。

```cpp
// 示例：0-1 背包的一维优化
vector<int> dp(W + 1, 0);
for (int i = 0; i < n; i++) {
    for (int j = W; j >= w[i]; j--) {  // 逆序更新
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
}

// 二维滚动数组示例
vector<vector<int>> dp(2, vector<int>(m));
int cur = 0, nxt = 1;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        // 状态转移
        dp[nxt][j] = ...;
    }
    swap(cur, nxt);
}
```

## 二分优化

在某些 DP 状态转移中，如果决策点具有单调性，可以使用二分查找来加速。

```cpp
// 示例：最长上升子序列 (LIS) 的 O(n log n) 优化
// 问题：找到最长严格递增子序列的长度
// 优化：维护一个数组 tail，tail[i] 表示长度为 i+1 的上升子序列的最小末尾元素

int lengthOfLIS(vector<int>& nums) {
    vector<int> tail;  // tail[i] = 长度为 i+1 的 LIS 的最小末尾元素
    
    for (int x : nums) {
        // 二分查找第一个 >= x 的位置
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) {
            tail.push_back(x);  // x 比所有元素都大
        } else {
            *it = x;  // 更新更小的末尾元素
        }
    }
    return tail.size();
}
```

## 矩阵优化

使用矩阵乘法来加速线性递推关系，常用于处理大规模的 DP 状态转移。

```cpp
// 示例：斐波那契数列的矩阵快速幂优化
// F(n) = F(n-1) + F(n-2) 可以写成矩阵形式：
// [F(n)  ]   [1 1] [F(n-1)]
// [F(n-1)] = [1 0] [F(n-2)]

struct Matrix {
    vector<vector<long long>> data;
    int n;
    
    Matrix(int n) : n(n), data(n, vector<long long>(n, 0)) {}
    
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return res;
    }
};

Matrix matrixPow(Matrix base, long long exp) {
    Matrix res(base.n);
    for (int i = 0; i < base.n; i++) res.data[i][i] = 1;  // 单位矩阵
    
    while (exp) {
        if (exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

long long fib(long long n) {
    if (n <= 1) return n;
    Matrix base(2);
    base.data[0][0] = base.data[0][1] = base.data[1][0] = 1;
    Matrix result = matrixPow(base, n - 1);
    return result.data[0][0];
}
```

## 斜率优化

当 DP 转移方程可以表示为 `dp[i] = min(dp[j] + slope * x[i] + intercept)` 的形式时，通过维护一个凸包来快速查询最优决策点。

```cpp
// 示例：最小化 dp[i] = min(dp[j] + (x[i] - x[j])^2 + C)
// 可以转化为：dp[i] = min(dp[j] + x[j]^2 - 2*x[i]*x[j]) + x[i]^2 + C
// 设 f(j) = dp[j] + x[j]^2, k = 2*x[i]
// 则 dp[i] = min(f(j) - k*x[j]) + x[i]^2 + C

// 使用单调队列维护下凸包
struct Point {
    long long x, y;
    double slope(Point p) {
        return (double)(y - p.y) / (x - p.x);
    }
};

deque<Point> dq;

void addPoint(long long x, long long y) {
    Point p = {x, y};
    while (dq.size() >= 2) {
        Point p1 = dq[dq.size() - 2];
        Point p2 = dq.back();
        if (p2.slope(p1) <= p.slope(p2)) {
            dq.pop_back();  // 不满足凸性，删除
        } else {
            break;
        }
    }
    dq.push_back(p);
}

long long query(long long k) {
    while (dq.size() >= 2) {
        Point p1 = dq[0];
        Point p2 = dq[1];
        if (p2.slope(p1) <= k) {
            dq.pop_front();  // 斜率更优的点在后面
        } else {
            break;
        }
    }
    Point p = dq.front();
    return p.y - k * p.x;  // 返回最优值
}
```

## 凸优化

处理状态转移函数是凸函数或凹函数时的优化方法。

```cpp
// 凸优化通常与斜率优化结合使用
// 当 DP 转移满足凸性时，可以使用二分搜索或三分搜索来优化

// 示例：wqs 二分（带权二分）
// 用于解决"恰好选 k 个物品"的问题
// 通过给选择操作添加惩罚项，将问题转化为无限制问题

long long wqsBinarySearch() {
    long long left = -1e9, right = 1e9;
    while (left < right) {
        long long mid = (left + right) / 2;
        auto [value, count] = solveWithPenalty(mid);
        if (count >= k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return solveWithPenalty(left - 1).first - (left - 1) * k;
}
```

## 四边形不等式优化

当 DP 转移满足四边形不等式性质时，可以优化决策点的查找范围。

```cpp
// 四边形不等式：w(i, j) + w(i', j') <= w(i, j') + w(i', j) (i <= i' <= j <= j')
// 如果满足，则决策点具有单调性：opt[i][j-1] <= opt[i][j] <= opt[i+1][j]

// 示例：区间 DP 的优化
// 原复杂度：O(n^3)，优化后：O(n^2)

int intervalDPOptimized(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n));  // 最优决策点
    
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            // 优化：只在 [opt[i][j-1], opt[i+1][j]] 范围内枚举
            int start = i < j - 1 ? opt[i][j-1] : i;
            int end = i + 1 < j ? opt[i+1][j] : j - 1;
            
            for (int k = start; k <= end; k++) {
                int cost = dp[i][k] + dp[k+1][j] + getCost(i, j);
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n-1];
}
```

## 数据结构优化

使用线段树、树状数组等数据结构来优化 DP 状态的查询或更新。

```cpp
// 示例：使用树状数组优化 DP 查询
// 问题：dp[i] = max(dp[j] + val[j]) where j < i and condition(j, i)

class FenwickTree {
    vector<long long> tree;
public:
    FenwickTree(int n) : tree(n + 1, LLONG_MIN) {}
    
    void update(int i, long long val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] = max(tree[i], val);
        }
    }
    
    long long query(int i) {
        long long res = LLONG_MIN;
        for (; i > 0; i -= i & -i) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

void dpWithFenwickTree(vector<int>& arr) {
    int n = arr.size();
    vector<long long> dp(n);
    FenwickTree ft(n);
    
    for (int i = 0; i < n; i++) {
        // 查询满足条件的最大 dp 值
        dp[i] = ft.query(arr[i]) + arr[i];
        // 更新树状数组
        ft.update(arr[i], dp[i]);
    }
}

// 示例：使用线段树优化区间查询
class SegmentTree {
    vector<long long> tree;
    int n;
    
    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = max(tree[node], val);
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = max(tree[2*node], tree[2*node+1]);
        }
    }
    
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return LLONG_MIN;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return max(query(2*node, start, mid, l, r),
                   query(2*node+1, mid+1, end, l, r));
    }
    
public:
    SegmentTree(int size) : n(size), tree(4 * size, LLONG_MIN) {}
    
    void update(int idx, long long val) {
        update(1, 0, n - 1, idx, val);
    }
    
    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
```

## 决策单调性

当 DP 的决策点具有单调性时，可以使用分治优化或单调队列等方法来加速。

```cpp
// 方法1：分治优化
// 适用于：dp[i] = min(dp[j] + cost(j, i))，且决策点单调

void solve(int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) / 2;
    int bestOpt = optL;
    long long bestVal = LLONG_MAX;
    
    // 在 [optL, min(optR, mid)] 范围内寻找最优决策点
    for (int j = optL; j <= min(optR, mid); j++) {
        long long val = dp[j] + cost(j, mid);
        if (val < bestVal) {
            bestVal = val;
            bestOpt = j;
        }
    }
    
    dp[mid] = bestVal;
    
    // 递归处理左右区间
    solve(l, mid - 1, optL, bestOpt);
    solve(mid + 1, r, bestOpt, optR);
}

// 方法2：单调队列优化
// 适用于：dp[i] = min(dp[j] + cost(j, i))，且 cost 函数满足特定性质

deque<int> dq;

void monotonicQueueDP() {
    for (int i = 0; i < n; i++) {
        // 移除不在决策范围内的点
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // 计算 dp[i]
        if (!dq.empty()) {
            int j = dq.front();
            dp[i] = dp[j] + cost(j, i);
        }
        
        // 维护单调性
        while (!dq.empty()) {
            int j = dq.back();
            if (dp[j] + cost(j, i + 1) >= dp[i] + cost(i, i + 1)) {
                dq.pop_back();
            } else {
                break;
            }
        }
        dq.push_back(i);
    }
}
```
