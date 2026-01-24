# 树形 DP

树形 DP 是在树结构上进行的动态规划。

## 树的直径

```cpp
// 问题：树的直径（树上最长路径）
// 状态：dp[u] 表示以 u 为根的子树中，从 u 出发的最长路径
//       同时维护全局答案 ans

vector<vector<int>> tree;
int ans = 0;

int dfs(int u, int parent) {
    int max1 = 0, max2 = 0;  // 最长和次长路径
    
    for (int v : tree[u]) {
        if (v == parent) continue;
        int len = dfs(v, u) + 1;
        if (len > max1) {
            max2 = max1;
            max1 = len;
        } else if (len > max2) {
            max2 = len;
        }
    }
    
    ans = max(ans, max1 + max2);  // 经过 u 的最长路径
    return max1;  // 返回从 u 出发的最长路径
}
```

## 常见应用

- 树的直径
- 树上背包
- 树的最大独立集
- 树的最小支配集
- 树的中心

## 基本模式

```cpp
// 树形 DP 的基本模式（DFS）
void dfs(int u, int parent) {
    // 初始化状态
    dp[u] = ...;
    
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u);  // 先处理子树
        // 合并子树状态
        dp[u] = merge(dp[u], dp[v]);
    }
}
```

## 注意事项

1. 需要记录父节点，避免重复访问
2. 通常使用 DFS 进行状态转移
3. 状态转移顺序：先处理子树，再合并到当前节点
