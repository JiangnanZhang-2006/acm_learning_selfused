# 其他容器

## tuple

- **元组**：可以存储多个不同类型值的容器（C++11）
- 类似于结构体，但更灵活
- 需要包含头文件：`#include <tuple>`
- **C++98 替代方案**：使用结构体

### 基本用法

```cpp
// 创建 tuple
tuple<int, string, double> t1(1, "hello", 3.14);
tuple<int, string, double> t2 = make_tuple(2, "world", 2.71);

// 访问元素（使用 get，索引从 0 开始）
int x = get<0>(t1);        // 获取第 0 个元素
string s = get<1>(t1);     // 获取第 1 个元素
double d = get<2>(t1);     // 获取第 2 个元素

// 修改元素
get<0>(t1) = 10;
get<1>(t1) = "test";

// 获取元素数量
int size = tuple_size<decltype(t1)>::value;  // size = 3
```

### 解包 tuple

```cpp
// 使用 tie 解包
int a;
string b;
double c;
tie(a, b, c) = t1;  // a=1, b="hello", c=3.14

// 忽略某些元素（使用 ignore）
tie(a, ignore, c) = t1;  // 只解包第 0 和第 2 个元素

// 使用结构化绑定（C++17，C++98/C++11 不支持）
// auto [x, y, z] = t1;
```

### 比较和交换

```cpp
// 比较（按字典序比较）
if (t1 < t2) { }   // 比较所有元素
if (t1 == t2) { }  // 所有元素相等

// 交换
swap(t1, t2);
```

### C++98 替代方案：使用结构体

```cpp
// C++98：使用结构体替代 tuple
struct MyTuple {
    int first;
    string second;
    double third;
    
    MyTuple(int f, string s, double t) : first(f), second(s), third(t) {}
};

// 使用
MyTuple t(1, "hello", 3.14);
int x = t.first;
string s = t.second;
double d = t.third;

// 比较需要手动实现
bool operator<(const MyTuple& a, const MyTuple& b) {
    if (a.first != b.first) return a.first < b.first;
    if (a.second != b.second) return a.second < b.second;
    return a.third < b.third;
}
```

### 常见用途

```cpp
// 1. 函数返回多个值
tuple<int, int> divide(int a, int b) {
    return make_tuple(a / b, a % b);
}

int quotient, remainder;
tie(quotient, remainder) = divide(10, 3);

// 2. 存储不同类型的组合数据
tuple<string, int, double> person("Alice", 25, 65.5);

// 3. 作为 map 的值类型（需要自定义比较函数）
map<tuple<int, int>, string> m;
m[make_tuple(1, 2)] = "value";
```

## pair

- **键值对**：用于存储两个值的容器
- 常用于 `map`、`multimap` 等容器
- 需要包含头文件：`#include <utility>` 或 `#include <map>`（通常已包含）

### pair 基本用法

```cpp
// 创建 pair
pair<string, int> p1("age", 25);
pair<string, int> p2 = make_pair("name", 30);
pair<string, int> p3 = {"score", 100};  // C++11 初始化列表

// 访问元素
string key = p1.first;    // 第一个元素
int value = p1.second;     // 第二个元素

// 修改元素
p1.first = "new_key";
p1.second = 30;

// 比较（按字典序比较）
if (p1 < p2) { }   // 先比较 first，再比较 second
if (p1 == p2) { }  // 两个元素都相等
```

### 与 make_pair 配合使用

```cpp
// make_pair：自动推导类型
auto p1 = make_pair(1, "hello");           // pair<int, const char*>
auto p2 = make_pair(3.14, 5);              // pair<double, int>

// 显式指定类型
pair<int, string> p3 = make_pair(1, "hello");

// 在容器中使用
map<string, int> m;
m.insert(make_pair("key", 10));  // 插入键值对
m["key"] = 20;                   // 也可以直接使用 []

// vector 存储 pair
vector<pair<int, int>> v;
v.push_back(make_pair(1, 2));
v.push_back({3, 4});  // C++11
```

### pair 常见用途

```cpp
// 1. 作为 map 的元素类型
map<string, int> m;
m.insert(make_pair("apple", 5));
m.insert(make_pair("banana", 3));

// 2. 函数返回两个值
pair<int, int> divide(int a, int b) {
    return make_pair(a / b, a % b);
}

pair<int, int> result = divide(10, 3);
int quotient = result.first;    // 3
int remainder = result.second;  // 1

// 3. 存储坐标点
vector<pair<int, int>> points;
points.push_back(make_pair(1, 2));
points.push_back(make_pair(3, 4));

// 4. 排序 pair 的 vector（按 first 排序，相同则按 second）
vector<pair<int, int>> v = {{3, 1}, {1, 2}, {2, 3}, {1, 1}};
sort(v.begin(), v.end());
// 结果：{{1, 1}, {1, 2}, {2, 3}, {3, 1}}
```

### 与 tuple 的对比

```cpp
// pair：只能存储两个值
pair<int, string> p(1, "hello");

// tuple：可以存储多个值（C++11）
tuple<int, string, double> t(1, "hello", 3.14);

// pair 的优势：更简单，性能更好
// tuple 的优势：更灵活，可以存储任意多个值
```

### C++11 特性

```cpp
// 使用初始化列表（C++11）
pair<int, string> p1 = {1, "hello"};

// 使用 tie 解包（C++11）
pair<int, string> p(1, "hello");
int a;
string b;
tie(a, b) = p;  // a=1, b="hello"

// 结构化绑定（C++17）
// auto [a, b] = p;  // C++17
```

## bitset

- **位集合**：固定大小的位序列，用于位操作
- 大小在编译时确定
- 需要包含头文件：`#include <bitset>`

```cpp
// 创建 bitset（大小为 8）
bitset<8> bs;                  // 全为 0
bitset<8> bs2("10101010");     // 从字符串初始化
bitset<8> bs3(42);             // 从整数初始化

// 访问和修改
bs[0] = 1;                     // 设置第 0 位
bool bit = bs[1];              // 获取第 1 位
bs.set();                      // 所有位设为 1
bs.reset();                    // 所有位设为 0
bs.flip();                     // 所有位取反
bs.flip(2);                    // 第 2 位取反

// 查询
bs.count();                    // 1 的个数
bs.size();                     // 总位数
bs.any();                      // 是否有 1
bs.none();                     // 是否全为 0
bs.all();                      // 是否全为 1（C++11）

// 转换
string s = bs.to_string();     // 转为字符串
unsigned long ul = bs.to_ulong();  // 转为无符号长整型

// 位运算
bitset<8> a("1010");
bitset<8> b("1100");
bitset<8> c = a & b;           // 按位与
bitset<8> d = a | b;           // 按位或
bitset<8> e = a ^ b;            // 按位异或
bitset<8> f = ~a;               // 按位取反
```

## boost

- **Boost 库**：C++ 社区开发的库集合，不是 STL 的一部分
- 需要单独安装和包含头文件
- 许多 Boost 库后来被纳入 C++11/14/17 标准库
- 官网：<https://www.boost.org/>

### 常用 Boost 库

```cpp
// 1. boost::shared_ptr - 智能指针（C++11 有 std::shared_ptr）
#include <boost/shared_ptr.hpp>
boost::shared_ptr<int> ptr(new int(10));

// 2. boost::unordered_map - 无序映射（C++11 有 std::unordered_map）
#include <boost/unordered_map.hpp>
boost::unordered_map<string, int> um;

// 3. boost::regex - 正则表达式（C++11 有 std::regex）
#include <boost/regex.hpp>
boost::regex pattern("\\d+");

// 4. boost::filesystem - 文件系统操作（C++17 有 std::filesystem）
#include <boost/filesystem.hpp>
boost::filesystem::path p("file.txt");

// 5. boost::algorithm - 算法扩展
#include <boost/algorithm/string.hpp>
string s = "hello world";
boost::to_upper(s);  // 转大写
boost::trim(s);       // 去除首尾空格
```

### C++11 标准库对应关系

许多 Boost 库的功能后来被纳入 C++ 标准：

- `boost::shared_ptr` → `std::shared_ptr` (C++11)
- `boost::unordered_map` → `std::unordered_map` (C++11)
- `boost::regex` → `std::regex` (C++11)
- `boost::filesystem` → `std::filesystem` (C++17)
- `boost::thread` → `std::thread` (C++11)

**注意：**

- Boost 不是 STL 的一部分，需要单独安装
- 在竞赛编程中，通常只使用标准库（STL）
- 如果可以使用 C++11，优先使用标准库而不是 Boost
