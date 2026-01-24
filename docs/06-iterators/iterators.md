# 迭代器

### 迭代器基本用法

```cpp
vector<int>::iterator it;
for (it = v.begin(); it != v.end(); ++it) {
    cout << *it << endl;
}
```

### 迭代器支持的操作符

迭代器支持多种操作符，不同类别的迭代器支持的操作符不同：

#### 所有迭代器都支持的操作符

```cpp
vector<int>::iterator it1, it2;

// 1. 解引用操作符 *
int value = *it1;        // 获取迭代器指向的元素
*it1 = 10;               // 修改迭代器指向的元素

// 2. 自增操作符 ++
++it1;                   // 前置自增（推荐，性能更好）
it1++;                   // 后置自增

// 3. 比较操作符 == !=
if (it1 == it2) { }      // 判断两个迭代器是否指向同一位置
if (it1 != it2) { }      // 判断两个迭代器是否指向不同位置

// 4. 赋值操作符 =
it1 = it2;               // 将 it2 赋值给 it1
```

#### 双向迭代器（list, set, map 等）额外支持

```cpp
list<int>::iterator it;

// 自减操作符 --
--it;                    // 前置自减（推荐）
it--;                    // 后置自减
```

#### 随机访问迭代器（vector, deque, string, array 等）额外支持

```cpp
vector<int>::iterator it;
int n = 5;

// 1. 算术操作符 + -
it + n;                  // 迭代器向前移动 n 个位置
it - n;                  // 迭代器向后移动 n 个位置
it += n;                 // 迭代器向前移动 n 个位置并赋值
it -= n;                 // 迭代器向后移动 n 个位置并赋值

// 2. 迭代器之间的减法
int distance = it2 - it1;  // 计算两个迭代器之间的距离

// 3. 比较操作符 < > <= >=
if (it1 < it2) { }       // 判断 it1 是否在 it2 之前
if (it1 > it2) { }       // 判断 it1 是否在 it2 之后
if (it1 <= it2) { }      // 判断 it1 是否在 it2 之前或相同
if (it1 >= it2) { }      // 判断 it1 是否在 it2 之后或相同

// 4. 下标操作符 []
int value = it[3];       // 访问迭代器后第 3 个元素（等价于 *(it + 3)）
it[0] = 10;              // 修改元素
```

#### 完整示例

```cpp
vector<int> v = {1, 2, 3, 4, 5};
vector<int>::iterator it = v.begin();

// 解引用
cout << *it << endl;           // 输出 1

// 自增
++it;
cout << *it << endl;           // 输出 2

// 算术运算
it = it + 2;
cout << *it << endl;           // 输出 4

// 下标访问
cout << it[1] << endl;         // 输出 5（it[1] 等价于 *(it + 1)）

// 迭代器距离（仅随机访问迭代器支持减法）
vector<int>::iterator it2 = v.end();
int dist = it2 - it;           // dist = 2（仅 vector, deque, string, array 支持）

// 比较
if (it < it2) {                // true
    cout << "it is before it2" << endl;
}

// 遍历
for (it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
```

#### 迭代器类别总结

| 迭代器类别 | 支持的容器 | 支持的操作符 |
| --------- | ---------- | ------------ |
| **输入迭代器** | istream_iterator | `*`, `++`, `==`, `!=` |
| **输出迭代器** | ostream_iterator | `*`, `++` |
| **前向迭代器** | forward_list | `*`, `++`, `==`, `!=` |
| **双向迭代器** | list, set, map | `*`, `++`, `--`, `==`, `!=` |
| **随机访问迭代器** | vector, deque, string, array | `*`, `++`, `--`, `+`, `-`, `+=`, `-=`, `[]`, `==`, `!=`, `<`, `>`, `<=`, `>=` |

**注意事项：**

- 随机访问迭代器支持所有操作符，功能最强大
- 双向迭代器不支持算术运算和下标访问
- 前向迭代器只能单向移动
- 使用 `++it` 比 `it++` 性能更好（避免临时对象）

### distance() 函数

`distance()` 函数用于计算两个迭代器之间的距离，适用于所有类型的迭代器：

```cpp
#include <iterator>

// 基本用法
vector<int> v = {1, 2, 3, 4, 5};
vector<int>::iterator it1 = v.begin();
vector<int>::iterator it2 = v.end();

// 计算距离
int dist = distance(it1, it2);  // dist = 5
int dist2 = distance(v.begin(), v.begin() + 3);  // dist2 = 3
```

**与迭代器减法的区别：**

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// 方法1：使用 distance()（适用于所有迭代器）
int d1 = distance(v.begin(), v.end());  // d1 = 5

// 方法2：使用减法（仅随机访问迭代器支持）
int d2 = v.end() - v.begin();           // d2 = 5（仅 vector, deque, string, array）

// 对于非随机访问迭代器（如 list），只能使用 distance()
list<int> lst = {1, 2, 3, 4, 5};
int d3 = distance(lst.begin(), lst.end());  // d3 = 5
// int d4 = lst.end() - lst.begin();       // 错误！list 不支持减法
```

**性能考虑：**

- **随机访问迭代器**（vector, deque, string, array）：`distance()` 和减法都是 O(1)
- **其他迭代器**（list, set, map 等）：`distance()` 是 O(n)，需要遍历计算

**常见用途：**

```cpp
// 1. 计算容器大小
vector<int> v = {1, 2, 3, 4, 5};
int size = distance(v.begin(), v.end());  // size = 5

// 2. 计算子区间大小
int sub_size = distance(v.begin() + 1, v.end() - 1);  // sub_size = 3

// 3. 在算法中使用
auto it = find(v.begin(), v.end(), 3);
if (it != v.end()) {
    int pos = distance(v.begin(), it);  // 找到元素的位置
    cout << "Found at position: " << pos << endl;
}

// 4. 与 list 等容器配合使用
list<int> lst = {1, 2, 3, 4, 5};
int count = distance(lst.begin(), lst.end());  // count = 5
```

**注意事项：**

- `distance(first, last)` 计算从 `first` 到 `last` 的距离（不包括 `last`）
- `first` 必须在 `last` 之前，否则行为未定义
- 对于非随机访问迭代器，`distance()` 会遍历整个区间，时间复杂度为 O(n)

### next() 和 prev() 函数

`next()` 和 `prev()` 用于在 **不修改原迭代器** 的前提下，返回“向前 / 向后移动若干步”之后的新迭代器。

```cpp
#include <iterator>

vector<int> v = {10, 20, 30, 40, 50};
auto it = v.begin();              // 指向 10

auto it2 = next(it);              // 指向 20，it 仍然指向 10
auto it3 = next(it, 3);           // 指向 40，it 仍然指向 10

auto it_end = v.end();            // 尾后迭代器
auto last = prev(it_end);         // 指向最后一个元素 50
auto last2 = prev(it_end, 2);     // 指向倒数第二个元素 40
```

**与 ++ / -- 的区别：**

- `++it` / `--it`：**修改** 原迭代器
- `next(it)` / `prev(it)`：**不修改** 原迭代器，返回一个新的迭代器

```cpp
auto it = v.begin();      // 指向 10
auto it2 = next(it, 2);   // it2 指向 30，it 还是指向 10
+it;                      // it 现在指向 20
```

**适用场景：**

- 在算法中需要“基于某个迭代器偏移几步”，又不想改动原迭代器时
- 与 `distance()` 搭配使用，更易读：

```cpp
auto mid = next(v.begin(), distance(v.begin(), v.end()) / 2);  // 找到中间位置
```

### 逆向迭代器（reverse_iterator）

逆向迭代器用于从后向前遍历容器：

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// 创建逆向迭代器
vector<int>::reverse_iterator rit;
for (rit = v.rbegin(); rit != v.rend(); ++rit) {
    cout << *rit << " ";  // 输出：5 4 3 2 1
}

// 获取逆向迭代器
v.rbegin();  // 指向最后一个元素
v.rend();    // 指向第一个元素之前的位置

// 逆向迭代器支持的操作
++rit;       // 向前移动（向容器开头方向）
--rit;       // 向后移动（向容器末尾方向）
*rit;        // 解引用
rit[2];      // 随机访问（仅随机访问迭代器支持）
```

**注意事项：**

- `rbegin()` 指向最后一个元素，`rend()` 指向第一个元素之前
- `++rit` 向容器开头方向移动，`--rit` 向容器末尾方向移动
- 支持逆向迭代器的容器：vector, deque, list, string, array, set, map 等

### 只读迭代器（const_iterator）

只读迭代器用于只读访问，不能修改元素：

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// const_iterator：只读迭代器
vector<int>::const_iterator cit;
for (cit = v.cbegin(); cit != v.cend(); ++cit) {
    cout << *cit << " ";  // 可以读取
    // *cit = 10;         // 错误！不能修改
}

// 获取只读迭代器
v.cbegin();  // const_iterator 版本的 begin()
v.cend();    // const_iterator 版本的 end()

// const 容器的迭代器自动是 const_iterator
const vector<int> cv = {1, 2, 3};
vector<int>::const_iterator it = cv.begin();  // 自动是 const_iterator
// *it = 10;  // 错误！不能修改
```

**const_iterator vs iterator：**

- `iterator`：可以读写元素
- `const_iterator`：只能读取元素，不能修改
- `cbegin()`, `cend()`：返回 const_iterator（C++11）

### 输入迭代器（input iterator）

输入迭代器用于从输入流读取数据：

```cpp
#include <iterator>

// istream_iterator：输入迭代器
istream_iterator<int> input_it(cin);      // 从 cin 读取 int
istream_iterator<int> input_end;          // 输入结束标志

// 读取数据
vector<int> v;
while (input_it != input_end) {
    v.push_back(*input_it);
    ++input_it;
}

// 或者使用 copy
copy(input_it, input_end, back_inserter(v));

// 特性：
// - 只能单向移动（++）
// - 只能读取（*）
// - 只能使用一次（读取后不能再次读取同一位置）
```

**输入迭代器特点：**

- 只能读取，不能写入
- 只能单向移动（`++`）
- 每个位置只能读取一次
- 支持的操作：`*`, `++`, `==`, `!=`

### 输出迭代器（output iterator）

输出迭代器用于向输出流写入数据：

```cpp
#include <iterator>

vector<int> v = {1, 2, 3, 4, 5};

// ostream_iterator：输出迭代器
ostream_iterator<int> output_it(cout, " ");  // 输出到 cout，用空格分隔

// 输出数据
copy(v.begin(), v.end(), output_it);  // 输出：1 2 3 4 5

// 或者手动使用
for (auto it = v.begin(); it != v.end(); ++it) {
    *output_it = *it;  // 写入
    ++output_it;
}

// 输出到文件（需要包含 <fstream>）
#include <fstream>
ofstream out("output.txt");
ostream_iterator<int> file_it(out, "\n");
copy(v.begin(), v.end(), file_it);
```

**输出迭代器特点：**

- 只能写入，不能读取
- 只能单向移动（`++`）
- 每个位置只能写入一次
- 支持的操作：`*`, `++`

### 迭代器适配器

```cpp
// 1. back_inserter：尾部插入迭代器
vector<int> v;
back_insert_iterator<vector<int>> back_it(v);
*back_it = 1;  // 等价于 v.push_back(1)
++back_it;
*back_it = 2;  // 等价于 v.push_back(2)

// 简化写法
back_inserter(v);  // 返回 back_insert_iterator

// 2. front_inserter：头部插入迭代器（仅 deque, list 支持）
deque<int> dq;
front_inserter(dq);  // 返回 front_insert_iterator

// 3. inserter：指定位置插入迭代器
vector<int> v = {1, 3, 4};
inserter(v, v.begin() + 1);  // 在指定位置插入
// 参数说明：
// - v: 目标容器
// - v.begin() + 1: 插入位置的迭代器（指向第二个元素的位置）
// 功能：创建一个迭代器，写入数据时在指定位置插入，插入后迭代器自动后移
```

**inserter 详细说明：**

```cpp
vector<int> v = {1, 3, 4};

// inserter(container, position) 创建一个插入迭代器
// position 是插入位置的迭代器
auto it = inserter(v, v.begin() + 1);
// v.begin() + 1 指向第二个元素（值为3）的位置
// 插入操作会在该位置之前插入新元素

// 使用示例
*it = 2;  // 在位置 v.begin() + 1 之前插入 2
// 结果：v = {1, 2, 3, 4}
// 注意：插入后，迭代器自动指向新插入元素的下一个位置

// 连续插入
*it = 5;  // 在当前位置之前插入 5
++it;
*it = 6;  // 继续插入 6
```

**使用示例：**

```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2;

// 使用 back_inserter 复制
copy(v1.begin(), v1.end(), back_inserter(v2));
// v2 = {1, 2, 3}

// 使用 ostream_iterator 输出
copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, ", "));
// 输出：1, 2, 3,

// 使用 inserter 在指定位置插入
vector<int> v3 = {1, 4, 5};
vector<int> v4 = {2, 3};
copy(v4.begin(), v4.end(), inserter(v3, v3.begin() + 1));
// 在 v3 的第二个位置（索引1）之前插入 v4 的所有元素
// 结果：v3 = {1, 2, 3, 4, 5}
```

### C++11 范围for循环

```cpp
for (auto& x : v) {
    cout << x << endl;
}
```
