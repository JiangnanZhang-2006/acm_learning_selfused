# 容器适配器

## queue

```cpp
queue<int> q;
q.push(x);             // 入队
q.pop();               // 出队
q.front();             // 队首
q.back();              // 队尾
q.empty(); q.size();   // 判断和大小
```

## stack

```cpp
stack<int> s;
s.push(x);             // 入栈
s.pop();               // 出栈
s.top();               // 栈顶
s.empty(); s.size();   // 判断和大小
```

## priority_queue

- **优先队列**：基于堆的数据结构，自动维护最大/最小元素
- 默认最大堆（大根堆）：顶部元素最大
- 需要包含头文件：`#include <queue>`

```cpp
// 默认最大堆
priority_queue<int> pq;
pq.push(x);           // 插入元素
pq.pop();             // 删除顶部元素（最大元素）
pq.top();             // 访问顶部元素（不删除）
pq.empty(); pq.size(); // 判断和大小

// 最小堆（小根堆）
priority_queue<int, vector<int>, greater<int>> min_pq;

// 自定义比较函数
struct Compare {
    bool operator()(int a, int b) {
        return a > b;  // 最小堆
    }
};
priority_queue<int, vector<int>, Compare> custom_pq;
```

**与 queue 的对比：**

- `queue`：先进先出（FIFO）
- `priority_queue`：优先级高的先出，不保证先进先出
