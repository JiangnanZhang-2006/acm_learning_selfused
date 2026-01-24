# numeric

- **数值算法头文件**：`#include <numeric>`
- 包含常用的数值计算函数

### 累加

```cpp
// accumulate：计算区间内所有元素的和
int sum = accumulate(v.begin(), v.end(), 0);  // 从0开始累加
int sum = accumulate(v.begin(), v.end(), 10); // 从10开始累加

// 自定义操作（C++98需要函数对象）
struct Multiply {
    int operator()(int a, int b) { return a * b; }
};
int product = accumulate(v.begin(), v.end(), 1, Multiply());  // 累乘
```

### 前缀和

```cpp
// partial_sum：计算前缀和
vector<int> v = {1, 2, 3, 4, 5};
vector<int> prefix(v.size());
partial_sum(v.begin(), v.end(), prefix.begin());
// prefix = {1, 3, 6, 10, 15}

// 自定义操作
partial_sum(v.begin(), v.end(), prefix.begin(), multiplies<int>());  // 前缀积
```

### 相邻差

```cpp
// adjacent_difference：计算相邻元素的差
vector<int> v = {1, 3, 6, 10, 15};
vector<int> diff(v.size());
adjacent_difference(v.begin(), v.end(), diff.begin());
// diff = {1, 2, 3, 4, 5}  (第一个元素保持不变)
```

### 内积

`inner_product()` 函数用于计算两个序列的内积（点积）。

**函数原型：**

```cpp
template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init);
```

**参数说明：**

- `first1, last1`：第一个序列的迭代器范围
- `first2`：第二个序列的起始迭代器（长度必须 >= 第一个序列）
- `init`：**初始值**（累加的起始值）

**最后一个参数 `0` 的作用：**

最后一个参数 `0` 是**初始值**，表示累加的起始值。内积的计算过程是：

1. 从 `init`（初始值）开始
2. 依次计算 `v1[i] * v2[i]` 并累加
3. 返回最终累加结果

```cpp
// inner_product：计算两个序列的内积（点积）
vector<int> v1 = {1, 2, 3};
vector<int> v2 = {4, 5, 6};

// 基本用法：最后一个参数 0 是初始值
int dot = inner_product(v1.begin(), v1.end(), v2.begin(), 0);
// 计算过程：
// 0 + (1*4) + (2*5) + (3*6) = 0 + 4 + 10 + 18 = 32
// 结果：dot = 32

// 如果初始值不是 0
int dot2 = inner_product(v1.begin(), v1.end(), v2.begin(), 10);
// 计算过程：
// 10 + (1*4) + (2*5) + (3*6) = 10 + 4 + 10 + 18 = 42
// 结果：dot2 = 42
```

**为什么需要初始值？**

1. **类型推导**：帮助编译器确定返回类型
2. **累加起点**：可以从非零值开始累加
3. **通用性**：支持自定义累加操作（见下方）

**自定义操作（完整版本）：**

`inner_product()` 还有完整版本，可以自定义"乘法"和"加法"操作：

```cpp
template <class InputIterator1, class InputIterator2, class T,
          class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init,
                BinaryOperation1 op1, BinaryOperation2 op2);
```

**参数说明：**

- `op1`：替代"乘法"的操作（默认是 `multiplies`）
- `op2`：替代"加法"的操作（默认是 `plus`）

**示例：**

```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = {4, 5, 6};

// 默认版本（乘法 + 加法）
int dot = inner_product(v1.begin(), v1.end(), v2.begin(), 0);
// 计算：0 + 1*4 + 2*5 + 3*6 = 32

// 自定义：使用加法代替乘法，使用乘法代替加法（计算 (a1+b1)*(a2+b2)*...）
int result = inner_product(v1.begin(), v1.end(), v2.begin(), 1,
                          plus<int>(), multiplies<int>());
// 计算：1 * (1+4) * (2+5) * (3+6) = 1 * 5 * 7 * 9 = 315

// 计算两个向量的曼哈顿距离（|a1-b1| + |a2-b2| + ...）
struct AbsDiff {
    int operator()(int a, int b) { return abs(a - b); }
};
int manhattan = inner_product(v1.begin(), v1.end(), v2.begin(), 0,
                              AbsDiff(), plus<int>());
// 计算：0 + |1-4| + |2-5| + |3-6| = 0 + 3 + 3 + 3 = 9
```

**常见用途：**

```cpp
// 1. 计算向量点积
vector<int> a = {1, 2, 3};
vector<int> b = {4, 5, 6};
int dot_product = inner_product(a.begin(), a.end(), b.begin(), 0);

// 2. 计算加权和
vector<int> values = {10, 20, 30};
vector<int> weights = {1, 2, 3};
int weighted_sum = inner_product(values.begin(), values.end(), 
                                  weights.begin(), 0);
// 计算：0 + 10*1 + 20*2 + 30*3 = 140

// 3. 从非零初始值开始
int sum = inner_product(v1.begin(), v1.end(), v2.begin(), 100);
// 从 100 开始累加
```

### 填充递增序列

`iota()` 函数用于填充一个区间，从起始值开始，每个元素递增 1。

**函数原型：**

```cpp
template <class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value);
```

**参数说明：**

- `first`：起始迭代器（要填充区间的开始位置）
- `last`：结束迭代器（要填充区间的结束位置，不包含）
- `value`：起始值（第一个元素的值）

**基本用法：**

```cpp
#include <numeric>  // iota 在 <numeric> 头文件中

// 示例1：从 0 开始填充
vector<int> v(5);                    // 创建大小为 5 的 vector
iota(v.begin(), v.end(), 0);         // 从 0 开始，每个元素 +1
// 结果：v = {0, 1, 2, 3, 4}

// 示例2：从 10 开始填充
vector<int> v2(5);
iota(v2.begin(), v2.end(), 10);      // 从 10 开始，每个元素 +1
// 结果：v2 = {10, 11, 12, 13, 14}

// 示例3：从负数开始
vector<int> v3(5);
iota(v3.begin(), v3.end(), -2);      // 从 -2 开始
// 结果：v3 = {-2, -1, 0, 1, 2}
```

**工作原理：**

`iota()` 会从 `value` 开始，依次将递增的值赋给区间 `[first, last)` 中的每个元素：

```cpp
vector<int> v(5);
iota(v.begin(), v.end(), 0);
// 等价于：
// v[0] = 0;
// v[1] = 1;
// v[2] = 2;
// v[3] = 3;
// v[4] = 4;
```

**常见用途：**

```cpp
// 1. 初始化索引数组
vector<int> indices(10);
iota(indices.begin(), indices.end(), 0);
// indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

// 2. 创建连续编号
vector<int> ids(100);
iota(ids.begin(), ids.end(), 1);     // 从 1 开始编号
// ids = {1, 2, 3, ..., 100}

// 3. 与其他容器配合
array<int, 5> arr;
iota(arr.begin(), arr.end(), 10);    // arr = {10, 11, 12, 13, 14}

deque<int> dq(5);
iota(dq.begin(), dq.end(), 5);       // dq = {5, 6, 7, 8, 9}

// 4. 用于排序索引（保持原数组不变）
vector<int> data = {30, 10, 20, 50, 40};
vector<int> indices(5);
iota(indices.begin(), indices.end(), 0);  // indices = {0, 1, 2, 3, 4}

// 按 data 的值对索引排序
sort(indices.begin(), indices.end(), 
     [&data](int i, int j) { return data[i] < data[j]; });
// indices = {1, 2, 0, 4, 3}（对应 data 中 {10, 20, 30, 40, 50} 的索引）
```

**注意事项：**

- `iota()` 是 C++11 引入的函数，需要包含 `<numeric>` 头文件
- 区间 `[first, last)` 必须有效且可写
- 每个元素的值是 `value + (当前位置 - first)`，即从 `value` 开始连续递增
- 适用于所有支持前向迭代器的容器（vector, deque, list, array 等）

**iota 的限制：**

`iota()` **只能每次加 1**，不能自定义步长。如果需要其他步长（如每次加 2、加 3 等），需要使用其他方法。

**实现自定义步长的方法：**

```cpp
// 方法1：使用循环（最简单直接）
vector<int> v(5);
int start = 0, step = 2;
for (int i = 0; i < v.size(); i++) {
    v[i] = start + i * step;  // 0, 2, 4, 6, 8
}

// 方法2：使用 generate 和函数对象（C++98）
struct StepIncrement {
    int value;
    int step;
    StepIncrement(int v, int s) : value(v), step(s) {}
    int operator()() {
        int result = value;
        value += step;
        return result;
    }
};

vector<int> v(5);
generate(v.begin(), v.end(), StepIncrement(0, 2));  // 从 0 开始，每次加 2
// 结果：v = {0, 2, 4, 6, 8}

// 方法3：使用 generate 和 lambda（C++11）
vector<int> v(5);
int start = 0, step = 2;
generate(v.begin(), v.end(), [&start, step]() {
    int result = start;
    start += step;
    return result;
});
// 结果：v = {0, 2, 4, 6, 8}

// 方法4：使用 transform 和 iota（先填充索引，再转换）
vector<int> indices(5);
iota(indices.begin(), indices.end(), 0);  // {0, 1, 2, 3, 4}
vector<int> v(5);
transform(indices.begin(), indices.end(), v.begin(), 
          [](int i) { return i * 2; });   // {0, 2, 4, 6, 8}
```

**完整示例：**

```cpp
// 生成偶数序列：0, 2, 4, 6, 8
vector<int> evens(5);
int val = 0;
generate(evens.begin(), evens.end(), [&val]() { 
    int result = val; 
    val += 2; 
    return result; 
});

// 生成奇数序列：1, 3, 5, 7, 9
vector<int> odds(5);
int val2 = 1;
generate(odds.begin(), odds.end(), [&val2]() { 
    int result = val2; 
    val2 += 2; 
    return result; 
});

// 生成 5 的倍数：0, 5, 10, 15, 20
vector<int> multiples(5);
int val3 = 0;
generate(multiples.begin(), multiples.end(), [&val3]() { 
    int result = val3; 
    val3 += 5; 
    return result; 
});
```

**C++98 替代方案（iota 本身）：**

```cpp
// 方法1：使用循环
vector<int> v(5);
for (int i = 0; i < v.size(); i++) {
    v[i] = i;              // 从 0 开始，每次加 1
    // 或 v[i] = start + i;  // 从 start 开始，每次加 1
}

// 方法2：使用 generate 和函数对象（每次加 1）
struct Increment {
    int value;
    Increment(int v) : value(v) {}
    int operator()() { return value++; }
};

vector<int> v(5);
generate(v.begin(), v.end(), Increment(0));  // 从 0 开始，每次加 1
```

### 最大公约数和最小公倍数

```cpp
// gcd, lcm：最大公约数和最小公倍数（C++17）
int a = 12, b = 18;
int g = gcd(a, b);  // g = 6
int l = lcm(a, b);  // l = 36

// C++98 替代方案：使用欧几里得算法
int gcd_cpp98(int a, int b) {
    return b == 0 ? a : gcd_cpp98(b, a % b);
}
int lcm_cpp98(int a, int b) {
    return a / gcd_cpp98(a, b) * b;
}
```
