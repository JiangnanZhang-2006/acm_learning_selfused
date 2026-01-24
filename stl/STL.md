# C++ 简要

## 目录

- [位运算](#位运算)
  - [基本运算符](#基本运算符)
  - [常用技巧](#常用技巧)
- [类与结构体](#类与结构体)
  - [结构体](#结构体)
  - [类](#类)
  - [构造函数与析构函数](#构造函数与析构函数)
- [输入输出 (cin/cout)](#输入输出-cincout)
  - [加速输入输出](#加速输入输出)
  - [文件重定向](#文件重定向)
  - [缓冲区操作](#缓冲区操作)
  - [格式化输出](#格式化输出)
- [默认形参值](#默认形参值)
- [引用](#引用)
  - [基本概念](#基本概念)
  - [引用作为函数参数](#引用作为函数参数)
  - [引用作为返回值](#引用作为返回值)
- [运算符重载](#运算符重载)
  - [运算符重载基本概念](#运算符重载基本概念)
  - [时间类示例](#时间类示例)
  - [常用运算符重载](#常用运算符重载)
    - [算术运算符](#算术运算符)
    - [比较运算符](#比较运算符)
    - [下标运算符](#下标运算符)
    - [函数调用运算符](#函数调用运算符)
    - [自增自减运算符](#自增自减运算符)
    - [赋值运算符](#赋值运算符)
    - [更多算术运算符](#更多算术运算符)
    - [更多比较运算符](#更多比较运算符)
    - [类型转换运算符](#类型转换运算符)
    - [成员访问运算符](#成员访问运算符)
    - [输入输出运算符（友元函数）](#输入输出运算符友元函数)
- [模板 (Template)](#模板-template)
  - [函数模板](#函数模板)
    - [基本语法](#基本语法)
    - [多类型参数](#多类型参数)
    - [显式指定类型](#显式指定类型)
    - [模板特化](#模板特化)
  - [类模板](#类模板)
    - [类模板基本语法](#类模板基本语法)
    - [类模板多类型参数](#类模板多类型参数)
    - [模板成员函数](#模板成员函数)
  - [模板注意事项](#模板注意事项)
- [STL 容器](#stl-容器)
  - [容器分类（按存储方式）](#容器分类按存储方式)
  - [vector](#vector)
  - [deque](#deque)
  - [list](#list)
  - [forward_list](#forward_list)
  - [string](#string)
    - [深拷贝特性](#深拷贝特性)
    - [基本操作](#基本操作)
  - [array](#array)
  - [queue](#queue)
  - [stack](#stack)
  - [priority_queue](#priority_queue)
  - [tuple](#tuple)
    - [基本用法](#基本用法)
    - [解包 tuple](#解包-tuple)
    - [比较和交换](#比较和交换)
    - [C++98 替代方案：使用结构体](#c98-替代方案使用结构体)
    - [常见用途](#常见用途)
  - [pair](#pair)
    - [pair 基本用法](#pair-基本用法)
    - [与 make_pair 配合使用](#与-make_pair-配合使用)
    - [pair 常见用途](#pair-常见用途)
    - [与 tuple 的对比](#与-tuple-的对比)
    - [C++11 特性](#c11-特性)
  - [bitset](#bitset)
  - [map](#map)
  - [set](#set)
  - [multimap](#multimap)
  - [multiset](#multiset)
  - [unordered_map](#unordered_map)
  - [unordered_set](#unordered_set)
  - [unordered_multimap](#unordered_multimap)
  - [unordered_multiset](#unordered_multiset)
  - [boost](#boost)
- [算法 (algorithm)](#算法-algorithm)
  - [排序](#排序)
  - [查找](#查找)
  - [其他常用算法](#其他常用算法)
  - [集合操作](#集合操作)
    - [set_union（并集）](#set_union并集)
    - [set_intersection（交集）](#set_intersection交集)
    - [set_difference（差集）](#set_difference差集)
    - [set_symmetric_difference（对称差集）](#set_symmetric_difference对称差集)
    - [includes（包含关系）](#includes包含关系)
    - [使用 set 容器进行集合操作](#使用-set-容器进行集合操作)
  - [remove 和 remove_if](#remove-和-remove_if)
- [numeric](#numeric)
  - [累加](#累加)
  - [前缀和](#前缀和)
  - [相邻差](#相邻差)
  - [内积](#内积)
  - [填充递增序列](#填充递增序列)
  - [最大公约数和最小公倍数](#最大公约数和最小公倍数)
- [迭代器](#迭代器)
  - [迭代器基本用法](#迭代器基本用法)
  - [迭代器支持的操作符](#迭代器支持的操作符)
    - [所有迭代器都支持的操作符](#所有迭代器都支持的操作符)
    - [双向迭代器（list, set, map 等）额外支持](#双向迭代器list-set-map-等额外支持)
    - [随机访问迭代器（vector, deque, string, array 等）额外支持](#随机访问迭代器vector-deque-string-array-等额外支持)
  - [distance() 函数](#distance-函数)
  - [next() 和 prev() 函数](#next-和-prev-函数)
  - [逆向迭代器（reverse_iterator）](#逆向迭代器reverse_iterator)
  - [只读迭代器（const_iterator）](#只读迭代器const_iterator)
  - [输入迭代器（input iterator）](#输入迭代器input-iterator)
  - [输出迭代器（output iterator）](#输出迭代器output-iterator)
  - [迭代器适配器](#迭代器适配器)
  - [C++11 范围for循环](#c11-范围for循环)
- [函数对象 (Functor)](#函数对象-functor)
  - [自定义比较函数](#自定义比较函数)
  - [Lambda 表达式（C++11）](#lambda-表达式c11)
  - [functional 头文件](#functional-头文件)
    - [算术函数对象](#算术函数对象)
    - [比较函数对象](#比较函数对象)
    - [逻辑函数对象](#逻辑函数对象)
    - [函数适配器（C++98）](#函数适配器c98)
- [注意事项](#注意事项)
  - [C++98 vs C++11](#c98-vs-c11)
  - [常用头文件](#常用头文件)

---

## 位运算

### 基本运算符

- `&` (按位与)：两个位都为1时结果为1
- `|` (按位或)：两个位至少一个为1时结果为1
- `^` (按位异或)：两个位不同时结果为1
- `~` (按位取反)：0变1，1变0
- `<<` (左移)：左移n位相当于乘以2^n
- `>>` (右移)：右移n位相当于除以2^n

### 常用技巧

- 判断奇偶：`n & 1`
- 取最低位1：`n & -n`
- 清除最低位1：`n & (n - 1)`
- 判断2的幂：`n > 0 && (n & (n - 1)) == 0`

## 类与结构体

### 结构体

- **默认访问权限**：`public`
- 适合存储数据

```cpp
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};
```

### 类

- **默认访问权限**：`private`
- 适合封装数据和方法

### 构造函数与析构函数

- **构造函数**：无返回值，用于初始化对象
- **析构函数**：无返回值，用于清理资源
- **临时对象**：`ClassName()` 创建临时对象

```cpp
class MyClass {
public:
    MyClass() { }           // 构造函数
    ~MyClass() { }          // 析构函数
};
```

## 输入输出 (cin/cout)

### 加速输入输出

```cpp
ios::sync_with_stdio(false);  // 关闭与stdio的同步
cin.tie(0);                   // 解除cin与cout的绑定
```

### 文件重定向

```cpp
// 方法1：使用ifstream
ifstream fin("input.txt");
fin >> x;
fin.close();

// 方法2：使用freopen
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
```

### 缓冲区操作

```cpp
cin.flush();    // 清空输入缓冲区
cout.flush();   // 清空输出缓冲区
cin.ignore();   // 忽略一个字符
cin.ignore(100, '\n');  // 忽略最多100个字符或直到换行
```

### 格式化输出

```cpp
cout << fixed << setprecision(2);  // 保留2位小数
cout << setw(10) << left << str;    // 左对齐，宽度10
cout << setw(10) << right << num;   // 右对齐，宽度10
cout << setfill('0') << setw(5);    // 用0填充，宽度5
```

## 默认形参值

- 函数参数可以设置默认值
- 默认参数必须从右到左连续

```cpp
void func(int a, int b = 10, int c = 20);
// func(1);      // a=1, b=10, c=20
// func(1, 2);   // a=1, b=2, c=20
// func(1, 2, 3); // a=1, b=2, c=3
```

## 引用

### 基本概念

- 引用是变量的别名
- 必须在声明时初始化
- 不能重新绑定到其他变量

```cpp
int a = 10;
int& ref = a;  // ref是a的引用
ref = 20;      // a也变成20
```

### 引用作为函数参数

```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

### 引用作为返回值

```cpp
int& getMax(int& a, int& b) {
    return a > b ? a : b;
}
```

## 运算符重载

### 运算符重载基本概念

- 允许为自定义类型定义运算符的行为
- 可以重载大部分运算符（`+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, `[]`, `()` 等）
- 不能重载的运算符：`::`, `.*`, `.`, `?:`

### 时间类示例

```cpp
class Clock {
private:
    int hour, minute, second;
public:
    Clock(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}
    
    // 重载 + 运算符（时间相加）
    Clock operator+(const Clock& other) const {
        Clock result;
        result.second = (this->second + other.second) % 60;
        int carry = (this->second + other.second) / 60;
        result.minute = (this->minute + other.minute + carry) % 60;
        carry = (this->minute + other.minute + carry) / 60;
        result.hour = (this->hour + other.hour + carry) % 24;
        return result;
    }
    
    // 重载 == 运算符（判断相等）
    bool operator==(const Clock& other) const {
        return hour == other.hour && 
               minute == other.minute && 
               second == other.second;
    }
    
    // 重载 < 运算符（比较大小）
    bool operator<(const Clock& other) const {
        if (hour != other.hour) return hour < other.hour;
        if (minute != other.minute) return minute < other.minute;
        return second < other.second;
    }
    
    // 重载 << 运算符（输出）
    friend ostream& operator<<(ostream& os, const Clock& c) {
        os << c.hour << ":" << c.minute << ":" << c.second;
        return os;
    }
    
    // 重载 >> 运算符（输入）
    friend istream& operator>>(istream& is, Clock& c) {
        is >> c.hour >> c.minute >> c.second;
        return is;
    }
};

// 使用示例
Clock c1(10, 30, 45);
Clock c2(2, 15, 20);
Clock c3 = c1 + c2;  // 时间相加
if (c1 == c2) { }    // 判断相等
if (c1 < c2) { }      // 比较大小
cout << c1;           // 输出时间
cin >> c1;            // 输入时间
```

### 常用运算符重载

#### 算术运算符

```cpp
// 重载 +
Point operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

// 重载 +=
Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
}
```

#### 比较运算符

```cpp
// 重载 ==
bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

// 重载 !=（通常基于 == 实现）
bool operator!=(const Point& other) const {
    return !(*this == other);
}
```

#### 下标运算符

```cpp
// 重载 []
int& operator[](int index) {
    return data[index];
}

const int& operator[](int index) const {
    return data[index];
}
```

#### 函数调用运算符

```cpp
// 重载 ()，使对象可以像函数一样调用
class Add {
    int value;
public:
    Add(int v) : value(v) {}
    int operator()(int x) const {
        return x + value;
    }
};

Add add5(5);
int result = add5(10);  // result = 15
```

#### 自增自减运算符

```cpp
// 重载前置 ++
Point& operator++() {
    x++;
    y++;
    return *this;  // 返回引用
}

// 重载后置 ++（使用 int 参数区分）
Point operator++(int) {
    Point temp = *this;  // 保存原值
    x++;
    y++;
    return temp;  // 返回原值
}

// 使用
Point p(1, 2);
++p;    // 前置：p 变成 (2, 3)，返回 p 的引用
p++;    // 后置：p 变成 (3, 4)，返回原值 (2, 3)
```

#### 赋值运算符

```cpp
// 重载 =（赋值运算符）
Point& operator=(const Point& other) {
    if (this != &other) {  // 避免自赋值
        x = other.x;
        y = other.y;
    }
    return *this;  // 返回引用以支持链式赋值
}

// 使用
Point p1(1, 2), p2(3, 4);
p1 = p2;        // p1 变成 (3, 4)
p1 = p2 = p3;   // 链式赋值
```

#### 更多算术运算符

```cpp
// 重载 -
Point operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

// 重载 -=
Point& operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

// 重载 *（标量乘法）
Point operator*(int scalar) const {
    return Point(x * scalar, y * scalar);
}

// 重载 /（标量除法）
Point operator/(int scalar) const {
    return Point(x / scalar, y / scalar);
}
```

#### 更多比较运算符

```cpp
// 重载 <
bool operator<(const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
}

// 重载 >
bool operator>(const Point& other) const {
    return other < *this;  // 基于 < 实现
}

// 重载 <=
bool operator<=(const Point& other) const {
    return !(*this > other);  // 基于 > 实现
}

// 重载 >=
bool operator>=(const Point& other) const {
    return !(*this < other);  // 基于 < 实现
}
```

#### 类型转换运算符

```cpp
// 重载类型转换运算符（转换为 double，表示距离原点的距离）
operator double() const {
    return sqrt(x * x + y * y);
}

// 使用
Point p(3, 4);
double dist = p;  // dist = 5.0（自动转换为 double）
```

#### 成员访问运算符

```cpp
// 重载 ->（智能指针示例）
class SmartPtr {
    Point* ptr;
public:
    SmartPtr(Point* p) : ptr(p) {}
    ~SmartPtr() { delete ptr; }
    
    Point* operator->() {
        return ptr;  // 返回指针，编译器会自动调用 ->
    }
    
    Point& operator*() {
        return *ptr;  // 解引用
    }
};

// 使用
SmartPtr sp(new Point(1, 2));
sp->x = 10;      // 通过 -> 访问成员
(*sp).y = 20;    // 通过 * 解引用访问
```

#### 输入输出运算符（友元函数）

```cpp
// 重载 <<（输出运算符，必须是友元函数）
friend ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;  // 返回流引用以支持链式输出
}

// 重载 >>（输入运算符，必须是友元函数）
friend istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;  // 返回流引用以支持链式输入
}

// 使用
Point p;
cin >> p;        // 输入
cout << p;       // 输出 "(x, y)"
cout << p1 << p2;  // 链式输出
```

## 模板 (Template)

### 函数模板

- **泛型编程**：编写与类型无关的代码
- 编译器根据调用时传入的参数类型自动实例化
- 避免为不同类型重复编写相同逻辑

#### 基本语法

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// 使用
int m1 = max(3, 5);           // T = int
double m2 = max(3.5, 2.1);    // T = double
```

#### 多类型参数

```cpp
template <typename T, typename U>
void print_pair(T a, U b) {
    cout << a << " " << b << endl;
}

print_pair(1, "hello");       // T = int, U = const char*
print_pair(3.14, 5);          // T = double, U = int
```

#### 显式指定类型

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int result = add<int>(3.5, 2.1);  // 显式指定 T = int，结果为 5
```

#### 模板特化

```cpp
// 通用模板
template <typename T>
void print(T value) {
    cout << value << endl;
}

// 特化版本（针对特定类型）
template <>
void print<string>(string value) {
    cout << "String: " << value << endl;
}
```

### 类模板

- 定义与类型无关的类
- STL 容器都是类模板（如 `vector<T>`, `map<K, V>`）

#### 类模板基本语法

```cpp
template <typename T>
class Stack {
private:
    vector<T> data;
public:
    void push(T item) {
        data.push_back(item);
    }
    T pop() {
        T item = data.back();
        data.pop_back();
        return item;
    }
    bool empty() {
        return data.empty();
    }
};

// 使用
Stack<int> intStack;
Stack<string> stringStack;
```

#### 类模板多类型参数

```cpp
template <typename Key, typename Value>
class Pair {
private:
    Key key;
    Value value;
public:
    Pair(Key k, Value v) : key(k), value(v) {}
    Key getKey() { return key; }
    Value getValue() { return value; }
};

Pair<string, int> p("age", 25);
```

#### 模板成员函数

```cpp
class MyClass {
public:
    template <typename T>
    void print(T value) {
        cout << value << endl;
    }
};

MyClass obj;
obj.print(10);        // 调用模板成员函数
obj.print("hello");
```

### 模板注意事项

#### C++98 限制

- 不支持 `auto` 类型推导
- 不支持变长参数模板（C++11）
- 不支持默认模板参数（部分支持）

#### 常见问题

```cpp
// 问题：模板函数定义必须在头文件中
// 原因：编译器需要看到完整定义才能实例化

// 解决方案1：在头文件中定义
// template.h
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// 解决方案2：显式实例化（C++98）
// template.cpp
template int max<int>(int, int);
template double max<double>(double, double);
```

## STL 容器

### 容器分类（按存储方式）

#### 线性存储容器（顺序容器）

元素在内存中按顺序存储，支持顺序访问和迭代器遍历：

- **`vector`** - 动态数组，支持随机访问
- **`deque`** - 双端队列，支持随机访问
- **`list`** - 双向链表，不支持随机访问
- **`forward_list`** - 单向链表，不支持随机访问（C++11）
- **`string`** - 字符串，类似 vector
- **`array`** - 固定大小数组（C++11）
- **`queue`** - 队列（适配器，通常基于 deque）
- **`stack`** - 栈（适配器，通常基于 deque 或 vector）
- **`priority_queue`** - 优先队列（适配器，基于堆）
- **`pair`** - 键值对（固定大小，两个值）
- **`tuple`** - 元组（固定大小，C++11）
- **`bitset`** - 位集合（固定大小）

**特点：**

- 元素按插入顺序存储
- 支持迭代器遍历
- 部分容器支持随机访问（vector, deque, string）

#### 非线性存储容器（关联容器/无序容器）

元素不是按顺序存储，基于树或哈希表结构：

- **`map`** - 有序映射（基于红黑树）
- **`set`** - 有序集合（基于红黑树）
- **`multimap`** - 允许重复键的有序映射（基于红黑树）
- **`multiset`** - 允许重复元素的有序集合（基于红黑树）
- **`unordered_map`** - 无序映射（基于哈希表，C++11）
- **`unordered_set`** - 无序集合（基于哈希表，C++11）
- **`unordered_multimap`** - 允许重复键的无序映射（基于哈希表，C++11）
- **`unordered_multiset`** - 允许重复元素的无序集合（基于哈希表，C++11）

**特点：**

- 元素按键值或哈希值存储
- 支持快速查找（O(log n) 或 O(1)）
- 有序容器（map, set）按键值排序
- 无序容器（unordered_map, unordered_set）不保证顺序

### vector

```cpp
vector<int> v;
v.push_back(x);        // 尾部插入
v.pop_back();          // 删除尾部元素
v.size();              // 大小
v.empty();             // 是否为空
v[i];                  // 访问元素
v.begin(); v.end();    // 迭代器
```

### deque

- **双端队列**：支持在两端高效插入和删除
- 随机访问：可以通过下标访问元素
- 性能：两端操作 O(1)，中间插入删除 O(n)

```cpp
deque<int> dq;
dq.push_back(x);       // 尾部插入
dq.push_front(x);      // 头部插入
dq.pop_back();         // 删除尾部
dq.pop_front();        // 删除头部
dq[i];                 // 随机访问
dq.front(); dq.back(); // 首尾元素
dq.size(); dq.empty(); // 大小和判断
dq.begin(); dq.end();  // 迭代器
```

### list

- **双向链表**：支持在任意位置高效插入和删除
- 不支持随机访问：不能通过下标访问，只能通过迭代器遍历
- 性能：插入、删除 O(1)，查找 O(n)
- 需要包含头文件：`#include <list>`

```cpp
list<int> lst;
lst.push_back(x);      // 尾部插入
lst.push_front(x);     // 头部插入
lst.pop_back();        // 删除尾部
lst.pop_front();        // 删除头部
lst.insert(it, x);     // 在迭代器位置插入
lst.erase(it);         // 删除迭代器指向的元素
lst.remove(x);         // 删除所有值为 x 的元素
lst.size(); lst.empty(); // 大小和判断
lst.front(); lst.back(); // 首尾元素
lst.begin(); lst.end(); // 迭代器
lst.sort();            // 排序（成员函数）
lst.merge(other);      // 合并两个有序链表
lst.unique();          // 删除连续重复元素
lst.reverse();         // 反转链表
```

**与 vector 的对比：**

- `vector`：动态数组，支持随机访问，尾部操作快，中间插入删除慢
- `list`：双向链表，不支持随机访问，任意位置插入删除快

**适用场景：**

- 需要频繁在中间位置插入删除
- 不需要随机访问
- 需要高效的合并、反转等操作

### forward_list

- **单向链表**：类似 `list`，但只能单向遍历（C++11）
- 不支持随机访问，只能从头开始遍历
- 性能：插入、删除 O(1)，查找 O(n)
- 需要包含头文件：`#include <forward_list>`
- **C++98 替代方案**：使用 `list`（双向链表）

```cpp
forward_list<int> fl;
fl.push_front(x);              // 头部插入
fl.pop_front();                // 删除头部元素
fl.insert_after(it, x);        // 在迭代器后插入
fl.erase_after(it);            // 删除迭代器后的元素
fl.front();                    // 第一个元素
fl.empty();                    // 是否为空
fl.begin(); fl.end();          // 迭代器

// 注意：没有 push_back, pop_back, back() 等操作
// 因为单向链表只能从头开始遍历
```

**与 list 的对比：**

- `list`：双向链表，支持双向遍历，有 `push_back`, `pop_back`, `back()` 等操作
- `forward_list`：单向链表，只能单向遍历，内存占用更小

### string

#### 深拷贝特性

- **实现了深拷贝**：赋值和拷贝时复制内容，而非指针
- 与 C 风格字符串（`char*`）不同，`string` 对象之间相互独立
- 修改一个 `string` 不会影响另一个

```cpp
string s1 = "hello";
string s2 = s1;        // 深拷贝，s2 有独立的内存空间
s1[0] = 'H';           // 只修改 s1，s2 仍然是 "hello"
cout << s1;            // 输出 "Hello"
cout << s2;            // 输出 "hello"

// 与 C 风格字符串对比
char* str1 = "hello";
char* str2 = str1;     // 浅拷贝，str2 指向同一块内存
// 修改 str1 会影响 str2（危险！）
```

#### 基本操作

```cpp
string s;
s += "abc";            // 追加
s.find("sub");         // 查找，返回位置或npos
s.substr(pos, len);    // 子串
s.length(); s.size();  // 长度
s.empty();             // 判断是否为空
s.clear();             // 清空
s.erase(pos, len);     // 删除子串
s.insert(pos, "str");  // 插入字符串
```

### array

- **固定大小数组**：类似 C 风格数组，但更安全（C++11）
- 大小在编译时确定，不能动态改变
- 需要包含头文件：`#include <array>`
- **C++98 替代方案**：使用 C 风格数组 `int arr[10]`

```cpp
// 创建固定大小数组
array<int, 10> arr;           // 10个int，未初始化
array<int, 5> arr2 = {1, 2, 3, 4, 5};  // 初始化

// 访问元素
arr[0] = 10;                  // 下标访问
arr.at(1) = 20;               // 带边界检查的访问
arr.front();                  // 第一个元素
arr.back();                   // 最后一个元素

// 大小和判断
arr.size();                   // 数组大小
arr.empty();                  // 是否为空（固定大小数组通常不为空）

// 迭代器
arr.begin(); arr.end();       // 迭代器

// 填充
arr.fill(0);                  // 所有元素填充为0
```

**与 vector 的对比：**

- `vector`：动态大小，可以改变
- `array`：固定大小，不能改变，但性能更好

### queue

```cpp
queue<int> q;
q.push(x);             // 入队
q.pop();               // 出队
q.front();             // 队首
q.back();              // 队尾
q.empty(); q.size();   // 判断和大小
```

### stack

```cpp
stack<int> s;
s.push(x);             // 入栈
s.pop();               // 出栈
s.top();               // 栈顶
s.empty(); s.size();   // 判断和大小
```

### priority_queue

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

### tuple

- **元组**：可以存储多个不同类型值的容器（C++11）
- 类似于结构体，但更灵活
- 需要包含头文件：`#include <tuple>`
- **C++98 替代方案**：使用结构体

#### 基本用法

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

#### 解包 tuple

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

#### 比较和交换

```cpp
// 比较（按字典序比较）
if (t1 < t2) { }   // 比较所有元素
if (t1 == t2) { }  // 所有元素相等

// 交换
swap(t1, t2);
```

#### C++98 替代方案：使用结构体

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

#### 常见用途

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

### pair

- **键值对**：用于存储两个值的容器
- 常用于 `map`、`multimap` 等容器
- 需要包含头文件：`#include <utility>` 或 `#include <map>`（通常已包含）

#### pair 基本用法

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

#### 与 make_pair 配合使用

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

#### pair 常见用途

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

#### 与 tuple 的对比

```cpp
// pair：只能存储两个值
pair<int, string> p(1, "hello");

// tuple：可以存储多个值（C++11）
tuple<int, string, double> t(1, "hello", 3.14);

// pair 的优势：更简单，性能更好
// tuple 的优势：更灵活，可以存储任意多个值
```

#### C++11 特性

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

### bitset

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

### map

```cpp
map<string, int> m;
m["key"] = value;      // 插入或修改
m.insert(make_pair("key", value));  // 插入
m.find("key");         // 查找，返回迭代器
m.count("key");        // 计数（0或1）
```

### set

```cpp
set<int> s;
s.insert(x);           // 插入
s.erase(x);            // 删除
s.find(x);             // 查找
s.count(x);            // 计数（0或1）
s.begin(); s.end();    // 迭代器
```

### multimap

- **允许重复键的映射**：类似 `map`，但允许多个相同键
- 基于红黑树，有序
- 需要包含头文件：`#include <map>`

```cpp
multimap<string, int> mm;
mm.insert(make_pair("key", 10));  // 插入
mm.insert(make_pair("key", 20));  // 可以插入相同键
mm.insert(make_pair("key", 30));

// 查找（返回第一个匹配的迭代器）
auto it = mm.find("key");

// 查找所有相同键的元素
pair<multimap<string, int>::iterator, multimap<string, int>::iterator> range;
range = mm.equal_range("key");
for (auto it = range.first; it != range.second; ++it) {
    cout << it->second << endl;  // 输出所有值为 "key" 的元素
}

// 计数
int count = mm.count("key");  // 返回键为 "key" 的元素个数

// 删除
mm.erase("key");              // 删除所有键为 "key" 的元素
```

**与 map 的对比：**

- `map`：键唯一，`m["key"]` 可以直接访问
- `multimap`：键可以重复，不能使用 `[]` 运算符

### multiset

- **允许重复元素的集合**：类似 `set`，但允许重复元素
- 基于红黑树，有序
- 需要包含头文件：`#include <set>`

```cpp
multiset<int> ms;
ms.insert(10);
ms.insert(20);
ms.insert(10);                // 可以插入重复元素

// 查找
auto it = ms.find(10);        // 返回第一个匹配的迭代器

// 查找所有相同元素
pair<multiset<int>::iterator, multiset<int>::iterator> range;
range = ms.equal_range(10);   // 返回首尾迭代器
for (auto it = range.first; it != range.second; ++it) {
    cout << *it << endl;      // 输出所有值为 10 的元素
}

// 计数
int count = ms.count(10);     // 返回值为 10 的元素个数

// 删除
ms.erase(10);                 // 删除所有值为 10 的元素
ms.erase(ms.find(10));        // 只删除第一个值为 10 的元素
```

**与 set 的对比：**

- `set`：元素唯一
- `multiset`：元素可以重复

### unordered_map

- **无序映射**：基于哈希表的键值对容器（C++11）
- 平均时间复杂度：插入、查找、删除 O(1)
- 与 `map` 的区别：无序，但查找更快
- 需要包含头文件：`#include <unordered_map>`

```cpp
unordered_map<string, int> um;
um["key"] = value;                    // 插入或修改
um.insert(make_pair("key", value));   // 插入
um.find("key");                       // 查找，返回迭代器
um.count("key");                      // 计数（0或1）
um.erase("key");                      // 删除
um.size(); um.empty();                // 大小和判断
```

**与 map 的对比：**

- `map`：有序，基于红黑树，查找 O(log n)
- `unordered_map`：无序，基于哈希表，查找 O(1) 平均

### unordered_set

- **无序集合**：基于哈希表的集合容器（C++11）
- 平均时间复杂度：插入、查找、删除 O(1)
- 与 `set` 的区别：无序，但查找更快
- 需要包含头文件：`#include <unordered_set>`

```cpp
unordered_set<int> us;
us.insert(x);          // 插入
us.erase(x);            // 删除
us.find(x);             // 查找，返回迭代器
us.count(x);            // 计数（0或1）
us.size(); us.empty();  // 大小和判断
us.begin(); us.end();   // 迭代器
```

**与 set 的对比：**

- `set`：有序，基于红黑树，查找 O(log n)
- `unordered_set`：无序，基于哈希表，查找 O(1) 平均

### unordered_multimap

- **允许重复键的无序映射**：类似 `unordered_map`，但允许多个相同键（C++11）
- 基于哈希表，无序
- 平均时间复杂度：插入、查找、删除 O(1)
- 需要包含头文件：`#include <unordered_map>`

```cpp
unordered_multimap<string, int> umm;
umm.insert(make_pair("key", 10));
umm.insert(make_pair("key", 20));  // 可以插入相同键

// 查找所有相同键的元素
auto range = umm.equal_range("key");
for (auto it = range.first; it != range.second; ++it) {
    cout << it->second << endl;
}

// 计数和删除
int count = umm.count("key");
umm.erase("key");             // 删除所有键为 "key" 的元素
```

### unordered_multiset

- **允许重复元素的无序集合**：类似 `unordered_set`，但允许重复元素（C++11）
- 基于哈希表，无序
- 平均时间复杂度：插入、查找、删除 O(1)
- 需要包含头文件：`#include <unordered_set>`

```cpp
unordered_multiset<int> ums;
ums.insert(10);
ums.insert(20);
ums.insert(10);                // 可以插入重复元素

// 查找所有相同元素
auto range = ums.equal_range(10);
for (auto it = range.first; it != range.second; ++it) {
    cout << *it << endl;
}

// 计数和删除
int count = ums.count(10);
ums.erase(10);                 // 删除所有值为 10 的元素
```

### boost

- **Boost 库**：C++ 社区开发的库集合，不是 STL 的一部分
- 需要单独安装和包含头文件
- 许多 Boost 库后来被纳入 C++11/14/17 标准库
- 官网：<https://www.boost.org/>

#### 常用 Boost 库

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

#### C++11 标准库对应关系

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

## 算法 (algorithm)

### 排序

```cpp
// sort：快速排序（不稳定）
sort(v.begin(), v.end());                    // 升序
sort(v.begin(), v.end(), greater<int>());   // 降序
sort(v.begin(), v.end(), cmp);              // 自定义比较

// stable_sort：稳定排序（保持相等元素的相对顺序）
stable_sort(v.begin(), v.end());                    // 升序
stable_sort(v.begin(), v.end(), greater<int>());   // 降序
stable_sort(v.begin(), v.end(), cmp);              // 自定义比较
```

**sort vs stable_sort：**

- **`sort`**：快速排序，平均时间复杂度 O(n log n)，不稳定
  - 相等元素的相对顺序可能改变
  - 性能更好，通常更快

- **`stable_sort`**：稳定排序，时间复杂度 O(n log² n) 或 O(n log n)
  - 保持相等元素的相对顺序不变
  - 性能稍慢，但保证稳定性

**使用场景：**

```cpp
// 示例：按分数排序，分数相同时保持原顺序
struct Student {
    string name;
    int score;
};

vector<Student> students = {
    {"Alice", 85},
    {"Bob", 90},
    {"Charlie", 85},
    {"David", 90}
};

// 使用 sort：相等分数的学生顺序可能改变
sort(students.begin(), students.end(), 
     [](const Student& a, const Student& b) { return a.score > b.score; });
// 结果：Bob 和 David 的顺序可能改变，Alice 和 Charlie 的顺序也可能改变

// 使用 stable_sort：相等分数的学生保持原顺序
stable_sort(students.begin(), students.end(), 
            [](const Student& a, const Student& b) { return a.score > b.score; });
// 结果：Bob 在 David 前面，Alice 在 Charlie 前面（保持原顺序）
```

### 查找

```cpp
find(v.begin(), v.end(), x);        // 查找元素
binary_search(v.begin(), v.end(), x);  // 二分查找（需有序）
lower_bound(v.begin(), v.end(), x);    // 第一个>=x的位置
upper_bound(v.begin(), v.end(), x);    // 第一个>x的位置
```

### 其他常用算法

```cpp
reverse(v.begin(), v.end());        // 反转
unique(v.begin(), v.end());         // 去重（需先排序）
max(a, b); min(a, b);               // 最值
swap(a, b);                         // 交换
```

### remove 和 remove_if

`remove()` 和 `remove_if()` 用于"移除"满足条件的元素，但**不会真正删除元素**，而是将不满足条件的元素移到前面，返回新的逻辑末尾迭代器。

**重要：** 需要配合 `erase()` 才能真正删除元素！

#### remove（移除指定值）

```cpp
vector<int> v = {1, 2, 3, 2, 4, 2, 5};

// remove：移除所有等于指定值的元素
auto it = remove(v.begin(), v.end(), 2);
// 结果：v = {1, 3, 4, 5, ?, ?, ?}（? 表示未定义的值）
// it 指向新的逻辑末尾（第一个 ? 的位置）

// 真正删除：需要配合 erase
v.erase(it, v.end());
// 结果：v = {1, 3, 4, 5}，大小变为 4
```

**工作原理：**

`remove()` 不会改变容器大小，只是将不满足条件的元素移到前面，满足条件的元素被"覆盖"到后面：

```cpp
vector<int> v = {1, 2, 3, 2, 4, 2, 5};
// 移除所有 2
auto it = remove(v.begin(), v.end(), 2);
// 过程：
// 1. 找到第一个 2，用后面的非 2 元素覆盖
// 2. 继续查找并覆盖
// 3. 最终：{1, 3, 4, 5, 2, 2, 5}（后面是未定义的值）
// 4. 返回指向第一个未定义值的迭代器
```

#### remove_if（条件移除）

```cpp
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// remove_if：移除满足条件的元素
auto it = remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// 移除所有偶数
// 结果：v = {1, 3, 5, 7, 9, ?, ?, ?, ?, ?}

// 真正删除
v.erase(it, v.end());
// 结果：v = {1, 3, 5, 7, 9}，大小变为 5
```

**完整示例：**

```cpp
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 1. 移除所有偶数
v.erase(remove_if(v.begin(), v.end(), 
                  [](int x) { return x % 2 == 0; }), 
        v.end());
// v = {1, 3, 5, 7, 9}

// 2. 移除所有小于 5 的元素
v.erase(remove_if(v.begin(), v.end(), 
                  [](int x) { return x < 5; }), 
        v.end());
// v = {5, 7, 9}

// 3. 移除所有负数
vector<int> v2 = {-1, 2, -3, 4, -5, 6};
v2.erase(remove_if(v2.begin(), v2.end(), 
                   [](int x) { return x < 0; }), 
         v2.end());
// v2 = {2, 4, 6}

// 4. 使用函数对象
struct IsEven {
    bool operator()(int x) { return x % 2 == 0; }
};
v.erase(remove_if(v.begin(), v.end(), IsEven()), v.end());
```

**remove vs remove_if：**

| 函数 | 条件 | 示例 |
| ---- | ---- | ---- |
| `remove(first, last, value)` | 移除等于 `value` 的元素 | `remove(v.begin(), v.end(), 2)` |
| `remove_if(first, last, pred)` | 移除满足谓词 `pred` 的元素 | `remove_if(v.begin(), v.end(), [](int x) { return x < 5; })` |

**注意事项：**

1. **必须配合 `erase()`**：`remove()` 和 `remove_if()` 不会真正删除元素，只是重新排列
2. **返回值：** 返回新的逻辑末尾迭代器，指向第一个"被移除"元素的位置
3. **容器大小不变：** 调用后容器大小不变，需要 `erase()` 来真正删除
4. **适用于顺序容器：** vector, deque, string, array 等
5. **不适用于关联容器：** map, set 等使用 `erase()` 成员函数

**错误用法：**

```cpp
// 错误：没有真正删除
vector<int> v = {1, 2, 3, 2, 4};
remove(v.begin(), v.end(), 2);
// v 的大小仍然是 5，只是元素被重新排列了

// 正确：配合 erase 使用
v.erase(remove(v.begin(), v.end(), 2), v.end());
// v 的大小变为 3
```

**与其他删除方法对比：**

```cpp
vector<int> v = {1, 2, 3, 2, 4, 2, 5};

// 方法1：使用 remove + erase（推荐）
v.erase(remove(v.begin(), v.end(), 2), v.end());
// 一次性删除所有 2

// 方法2：使用循环 + erase（不推荐，效率低）
for (auto it = v.begin(); it != v.end(); ) {
    if (*it == 2) {
        it = v.erase(it);  // erase 返回下一个迭代器
    } else {
        ++it;
    }
}
// 每次删除都要移动元素，效率低

// 方法3：对于 list，使用成员函数（更高效）
list<int> lst = {1, 2, 3, 2, 4, 2, 5};
lst.remove(2);  // list 的成员函数，直接删除
// lst = {1, 3, 4, 5}
```

### 集合操作

集合操作函数用于处理两个**已排序**的序列，执行集合运算。**注意：输入序列必须是有序的！**

#### set_union（并集）

计算两个集合的并集（所有出现在任一集合中的元素）：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {3, 4, 5, 6, 7};
vector<int> result;

// 计算并集
set_union(v1.begin(), v1.end(), 
          v2.begin(), v2.end(),
          back_inserter(result));
// result = {1, 2, 3, 4, 5, 6, 7}（去重，有序）

// 如果结果容器大小已知，可以预分配
vector<int> result2(v1.size() + v2.size());
auto it = set_union(v1.begin(), v1.end(), 
                    v2.begin(), v2.end(),
                    result2.begin());
result2.resize(it - result2.begin());  // 调整大小
```

#### set_intersection（交集）

计算两个集合的交集（同时出现在两个集合中的元素）：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {3, 4, 5, 6, 7};
vector<int> result;

// 计算交集
set_intersection(v1.begin(), v1.end(), 
                 v2.begin(), v2.end(),
                 back_inserter(result));
// result = {3, 4, 5}
```

#### set_difference（差集）

计算两个集合的差集（在第一个集合中但不在第二个集合中的元素）：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {3, 4, 5, 6, 7};
vector<int> result;

// 计算差集：v1 - v2
set_difference(v1.begin(), v1.end(), 
              v2.begin(), v2.end(),
              back_inserter(result));
// result = {1, 2}（在 v1 中但不在 v2 中）

// 计算差集：v2 - v1
vector<int> result2;
set_difference(v2.begin(), v2.end(), 
              v1.begin(), v1.end(),
              back_inserter(result2));
// result2 = {6, 7}（在 v2 中但不在 v1 中）
```

#### set_symmetric_difference（对称差集）

计算两个集合的对称差集（在任一集合中但不在两个集合交集中的元素）：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {3, 4, 5, 6, 7};
vector<int> result;

// 计算对称差集
set_symmetric_difference(v1.begin(), v1.end(), 
                        v2.begin(), v2.end(),
                        back_inserter(result));
// result = {1, 2, 6, 7}（只在 v1 或只在 v2 中的元素）
```

#### includes（包含关系）

判断第一个集合是否包含第二个集合（第二个集合的所有元素是否都在第一个集合中）：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
vector<int> v2 = {2, 4, 6};

// 判断 v1 是否包含 v2
bool contains = includes(v1.begin(), v1.end(), 
                         v2.begin(), v2.end());
// contains = true（v1 包含 v2 的所有元素）

vector<int> v3 = {2, 4, 8};
bool contains2 = includes(v1.begin(), v1.end(), 
                          v3.begin(), v3.end());
// contains2 = false（v1 不包含 8）
```

**完整示例：**

```cpp
#include <algorithm>
#include <vector>
#include <iterator>

vector<int> set1 = {1, 2, 3, 4, 5};
vector<int> set2 = {3, 4, 5, 6, 7};
vector<int> result;

// 1. 并集
set_union(set1.begin(), set1.end(), 
          set2.begin(), set2.end(),
          back_inserter(result));
// result = {1, 2, 3, 4, 5, 6, 7}

// 2. 交集
result.clear();
set_intersection(set1.begin(), set1.end(), 
                set2.begin(), set2.end(),
                back_inserter(result));
// result = {3, 4, 5}

// 3. 差集
result.clear();
set_difference(set1.begin(), set1.end(), 
              set2.begin(), set2.end(),
              back_inserter(result));
// result = {1, 2}

// 4. 对称差集
result.clear();
set_symmetric_difference(set1.begin(), set1.end(), 
                        set2.begin(), set2.end(),
                        back_inserter(result));
// result = {1, 2, 6, 7}

// 5. 包含关系
bool is_subset = includes(set1.begin(), set1.end(), 
                         set2.begin(), set2.end());
// is_subset = false（set1 不包含 set2）
```

**注意事项：**

- **输入序列必须是有序的**（通常使用 `sort()` 排序）
- 所有函数都返回输出迭代器，指向结果序列的末尾
- 结果序列自动去重并保持有序
- 时间复杂度：O(n + m)，其中 n 和 m 是两个序列的长度
- 可以自定义比较函数（用于自定义排序规则）

**自定义比较函数：**

```cpp
// 降序排列的集合操作
vector<int> v1 = {5, 4, 3, 2, 1};
vector<int> v2 = {7, 5, 4, 3};
vector<int> result;

set_union(v1.begin(), v1.end(), 
          v2.begin(), v2.end(),
          back_inserter(result),
          greater<int>());  // 使用降序比较
// result = {7, 5, 4, 3, 2, 1}
```

#### 使用 set 容器进行集合操作

如果使用 `set` 容器，**不需要先排序**（set 本身已有序且去重），可以直接使用集合操作函数：

```cpp
#include <set>
#include <algorithm>
#include <iterator>

set<int> s1 = {1, 2, 3, 4, 5};
set<int> s2 = {3, 4, 5, 6, 7};
set<int> result;

// 1. 并集（结果也是 set，自动去重有序）
set_union(s1.begin(), s1.end(), 
          s2.begin(), s2.end(),
          inserter(result, result.begin()));
// result = {1, 2, 3, 4, 5, 6, 7}

// 2. 交集
result.clear();
set_intersection(s1.begin(), s1.end(), 
                 s2.begin(), s2.end(),
                 inserter(result, result.begin()));
// result = {3, 4, 5}

// 3. 差集
result.clear();
set_difference(s1.begin(), s1.end(), 
               s2.begin(), s2.end(),
               inserter(result, result.begin()));
// result = {1, 2}

// 4. 对称差集
result.clear();
set_symmetric_difference(s1.begin(), s1.end(), 
                        s2.begin(), s2.end(),
                        inserter(result, result.begin()));
// result = {1, 2, 6, 7}

// 5. 包含关系
bool is_subset = includes(s1.begin(), s1.end(), 
                          s2.begin(), s2.end());
// is_subset = false
```

**set vs vector 的区别：**

| 特性 | vector | set |
| ---- | ------ | --- |
| **是否需要排序** | ✅ 需要先 `sort()` | ❌ 不需要（已有序） |
| **是否自动去重** | ❌ 需要 `unique()` | ✅ 自动去重 |
| **结果容器** | `vector` + `back_inserter` | `set` + `inserter` |
| **性能** | 排序 O(n log n) | 插入 O(log n) |

**使用 set 的优势：**

1. **无需排序**：set 本身已有序
2. **自动去重**：结果自动去重
3. **高效查找**：结果也是 set，查找 O(log n)
4. **代码更简洁**：不需要预处理步骤

**完整示例：**

```cpp
set<int> s1 = {1, 2, 3, 4, 5};
set<int> s2 = {3, 4, 5, 6, 7};
set<int> union_set, intersection_set, difference_set;

// 并集
set_union(s1.begin(), s1.end(), 
          s2.begin(), s2.end(),
          inserter(union_set, union_set.begin()));
// union_set = {1, 2, 3, 4, 5, 6, 7}

// 交集
set_intersection(s1.begin(), s1.end(), 
                 s2.begin(), s2.end(),
                 inserter(intersection_set, intersection_set.begin()));
// intersection_set = {3, 4, 5}

// 差集
set_difference(s1.begin(), s1.end(), 
               s2.begin(), s2.end(),
               inserter(difference_set, difference_set.begin()));
// difference_set = {1, 2}

// 检查包含关系
set<int> subset = {2, 4};
bool contains = includes(s1.begin(), s1.end(), 
                        subset.begin(), subset.end());
// contains = true（s1 包含 subset）
```

**注意事项：**

- 使用 `inserter(result, result.begin())` 而不是 `back_inserter(result)`
- set 不支持 `back_inserter`（没有 `push_back`）
- 结果直接是 set，自动有序且去重
- 如果结果容器是空的，`inserter` 的第二个参数可以是 `result.begin()`

## numeric

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

## 迭代器

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

## 函数对象 (Functor)

### 自定义比较函数

```cpp
struct Compare {
    bool operator()(const int& a, const int& b) {
        return a > b;  // 降序
    }
};
sort(v.begin(), v.end(), Compare());
```

### Lambda 表达式（C++11）

Lambda 表达式是一种匿名函数，可以在需要函数对象的地方直接定义，使代码更简洁。

**基本语法：**

```cpp
[捕获列表](参数列表) -> 返回类型 { 函数体 }
```

**最简单的形式：**

```cpp
// 无参数，无返回值
auto f = []() { cout << "Hello" << endl; };
f();  // 输出 Hello

// 有参数
auto add = [](int a, int b) { return a + b; };
int sum = add(3, 5);  // sum = 8

// 在算法中使用
vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
// v = {5, 4, 3, 1, 1}（降序）
```

**捕获列表：**

Lambda 可以通过捕获列表访问外部变量：

```cpp
int x = 10;
int y = 20;

// 1. [=]：按值捕获所有外部变量
auto f1 = [=]() { return x + y; };  // 捕获 x 和 y 的副本
// f1() = 30

// 2. [&]：按引用捕获所有外部变量
auto f2 = [&]() { x++; return x + y; };  // 修改原变量
// f2() = 31, x 变成 11

// 3. [x, y]：按值捕获指定变量
auto f3 = [x, y]() { return x + y; };  // 只捕获 x 和 y

// 4. [&x, y]：混合捕获（x 按引用，y 按值）
auto f4 = [&x, y]() { x++; return x + y; };

// 5. [=, &x]：按值捕获所有，但 x 按引用
auto f5 = [=, &x]() { x++; return x + y; };

// 6. [&, x]：按引用捕获所有，但 x 按值
auto f6 = [&, x]() { y++; return x + y; };
```

**在算法中使用 Lambda：**

```cpp
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 1. 使用 lambda 作为比较函数
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
// 降序排序

// 2. 使用 lambda 作为谓词（返回 bool）
int count = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// 统计偶数个数

// 3. 使用 lambda 进行转换
vector<int> result(v.size());
transform(v.begin(), v.end(), result.begin(), [](int x) { return x * 2; });
// 每个元素乘以 2

// 4. 使用 lambda 查找
auto it = find_if(v.begin(), v.end(), [](int x) { return x > 5; });
// 找到第一个大于 5 的元素

// 5. 使用 lambda 删除
v.erase(remove_if(v.begin(), v.end(), [](int x) { return x < 5; }), v.end());
// 删除所有小于 5 的元素
```

**捕获外部变量示例：**

```cpp
int threshold = 5;
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 使用外部变量 threshold
int count = count_if(v.begin(), v.end(), 
                     [threshold](int x) { return x > threshold; });
// 统计大于 threshold 的元素个数

// 修改外部变量
int sum = 0;
for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
// sum = 55（累加所有元素）
```

**返回类型：**

```cpp
// 自动推导返回类型（简单情况）
auto add = [](int a, int b) { return a + b; };

// 显式指定返回类型
auto divide = [](double a, double b) -> double {
    if (b == 0) return 0.0;
    return a / b;
};

// 复杂返回类型
auto complex = [](int x) -> pair<int, int> {
    return make_pair(x * 2, x * 3);
};
```

**Lambda vs 函数对象：**

```cpp
// 方法1：使用函数对象（C++98）
struct Compare {
    bool operator()(int a, int b) { return a > b; }
};
sort(v.begin(), v.end(), Compare());

// 方法2：使用 lambda（C++11，更简洁）
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

**常见用途：**

```cpp
// 1. 排序
vector<pair<int, string>> v = {{3, "c"}, {1, "a"}, {2, "b"}};
sort(v.begin(), v.end(), [](const pair<int, string>& a, 
                            const pair<int, string>& b) {
    return a.first < b.first;  // 按第一个元素排序
});

// 2. 查找
vector<int> v = {1, 2, 3, 4, 5};
auto it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });

// 3. 转换
vector<int> v1 = {1, 2, 3};
vector<int> v2(v1.size());
transform(v1.begin(), v1.end(), v2.begin(), 
          [](int x) { return x * x; });  // 平方

// 4. 累加
int sum = accumulate(v.begin(), v.end(), 0, 
                     [](int a, int b) { return a + b * b; });  // 平方和

// 5. 条件删除
v.erase(remove_if(v.begin(), v.end(), 
                  [](int x) { return x < 0; }), v.end());
```

**注意事项：**

- Lambda 是 C++11 特性，C++98 不支持
- 捕获列表中的变量在 lambda 创建时捕获（按值）或绑定（按引用）
- 按值捕获的变量在 lambda 内部是只读的（除非使用 `mutable`）
- 按引用捕获要注意变量的生命周期
- Lambda 可以赋值给 `auto` 变量或 `function` 对象

**C++98 替代方案：**

```cpp
// C++98：使用函数对象
struct GreaterThan {
    int threshold;
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int x) { return x > threshold; }
};

int count = count_if(v.begin(), v.end(), GreaterThan(5));
```

### functional 头文件

`<functional>` 头文件提供了许多预定义的函数对象，可以直接使用，无需自己定义。

#### 算术函数对象

```cpp
#include <functional>

// 1. plus：加法
plus<int> add;
int result = add(3, 5);  // result = 8
// 等价于：int result = 3 + 5;

// 2. minus：减法
minus<int> sub;
int result2 = sub(10, 3);  // result2 = 7

// 3. multiplies：乘法
multiplies<int> mul;
int result3 = mul(4, 5);  // result3 = 20

// 4. divides：除法
divides<int> div;
int result4 = div(20, 4);  // result4 = 5

// 5. modulus：取模
modulus<int> mod;
int result5 = mod(10, 3);  // result5 = 1

// 6. negate：取反（一元操作）
negate<int> neg;
int result6 = neg(5);  // result6 = -5
```

**在算法中使用：**

```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = {4, 5, 6};
vector<int> result(3);

// 使用 transform 和 plus 进行元素相加
transform(v1.begin(), v1.end(), v2.begin(), result.begin(), plus<int>());
// result = {5, 7, 9}

// 使用 transform 和 multiplies 进行元素相乘
transform(v1.begin(), v1.end(), v2.begin(), result.begin(), multiplies<int>());
// result = {4, 10, 18}
```

#### 比较函数对象

```cpp
#include <functional>

// 1. equal_to：等于
equal_to<int> eq;
bool b1 = eq(5, 5);  // b1 = true

// 2. not_equal_to：不等于
not_equal_to<int> ne;
bool b2 = ne(5, 3);  // b2 = true

// 3. greater：大于
greater<int> gt;
bool b3 = gt(5, 3);  // b3 = true

// 4. less：小于
less<int> lt;
bool b4 = lt(3, 5);  // b4 = true

// 5. greater_equal：大于等于
greater_equal<int> ge;
bool b5 = ge(5, 5);  // b5 = true

// 6. less_equal：小于等于
less_equal<int> le;
bool b6 = le(3, 5);  // b6 = true
```

**在算法中使用：**

```cpp
vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// 使用 greater 降序排序
sort(v.begin(), v.end(), greater<int>());
// v = {9, 6, 5, 4, 3, 2, 1, 1}

// 使用 less 升序排序（默认）
sort(v.begin(), v.end(), less<int>());
// v = {1, 1, 2, 3, 4, 5, 6, 9}

// 使用 equal_to 查找相等元素
auto it = find_if(v.begin(), v.end(), bind2nd(equal_to<int>(), 5));
// 找到第一个等于 5 的元素
```

#### 逻辑函数对象

```cpp
#include <functional>

// 1. logical_and：逻辑与
logical_and<bool> land;
bool b1 = land(true, false);  // b1 = false

// 2. logical_or：逻辑或
logical_or<bool> lor;
bool b2 = lor(true, false);  // b2 = true

// 3. logical_not：逻辑非（一元操作）
logical_not<bool> lnot;
bool b3 = lnot(true);  // b3 = false
```

#### 函数适配器（C++98）

**注意：** 这些适配器在 C++11 中已弃用，推荐使用 `bind` 或 `lambda`。

```cpp
#include <functional>

// 1. bind1st：绑定第一个参数
vector<int> v = {1, 2, 3, 4, 5};
int count = count_if(v.begin(), v.end(), bind1st(less<int>(), 3));
// 计算小于 3 的元素个数（等价于 count_if(..., [](int x) { return 3 < x; })）
// count = 2（元素 1, 2）

// 2. bind2nd：绑定第二个参数
int count2 = count_if(v.begin(), v.end(), bind2nd(less<int>(), 3));
// 计算小于 3 的元素个数（等价于 count_if(..., [](int x) { return x < 3; })）
// count2 = 2（元素 1, 2）

// 3. not1：对一元谓词取反
not1(logical_not<bool>())  // 很少使用

// 4. not2：对二元谓词取反
not2(less<int>())  // 等价于 greater_equal<int>()
```

**C++11 替代方案（推荐）：**

```cpp
// 使用 lambda（C++11）
int count = count_if(v.begin(), v.end(), [](int x) { return x < 3; });

// 使用 bind（C++11）
#include <functional>
using namespace std::placeholders;
int count2 = count_if(v.begin(), v.end(), bind(less<int>(), _1, 3));
```

#### functional 使用示例

```cpp
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>

vector<int> v = {1, 2, 3, 4, 5};

// 1. 使用 plus 累加
int sum = accumulate(v.begin(), v.end(), 0, plus<int>());
// sum = 15

// 2. 使用 multiplies 累乘
int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
// product = 120

// 3. 使用 greater 降序排序
sort(v.begin(), v.end(), greater<int>());
// v = {5, 4, 3, 2, 1}

// 4. 使用 less 升序排序
sort(v.begin(), v.end(), less<int>());
// v = {1, 2, 3, 4, 5}

// 5. 使用 equal_to 统计相等元素
int count = count_if(v.begin(), v.end(), bind2nd(equal_to<int>(), 3));
// count = 1（有一个元素等于 3）
```

**常用函数对象总结：**

| 类别 | 函数对象 | 操作 | 示例 |
| ---- | -------- | ---- | ---- |
| **算术** | `plus<T>` | `a + b` | `plus<int>()(3, 5)` → 8 |
| | `minus<T>` | `a - b` | `minus<int>()(10, 3)` → 7 |
| | `multiplies<T>` | `a * b` | `multiplies<int>()(4, 5)` → 20 |
| | `divides<T>` | `a / b` | `divides<int>()(20, 4)` → 5 |
| | `modulus<T>` | `a % b` | `modulus<int>()(10, 3)` → 1 |
| | `negate<T>` | `-a` | `negate<int>()(5)` → -5 |
| **比较** | `equal_to<T>` | `a == b` | `equal_to<int>()(5, 5)` → true |
| | `not_equal_to<T>` | `a != b` | `not_equal_to<int>()(5, 3)` → true |
| | `greater<T>` | `a > b` | `greater<int>()(5, 3)` → true |
| | `less<T>` | `a < b` | `less<int>()(3, 5)` → true |
| | `greater_equal<T>` | `a >= b` | `greater_equal<int>()(5, 5)` → true |
| | `less_equal<T>` | `a <= b` | `less_equal<int>()(3, 5)` → true |
| **逻辑** | `logical_and<T>` | `a && b` | `logical_and<bool>()(true, false)` → false |
| | `logical_or<T>` | `a \|\| b` | `logical_or<bool>()(true, false)` → true |
| | `logical_not<T>` | `!a` | `logical_not<bool>()(true)` → false |

## 注意事项

### C++98 vs C++11

- **C++98不支持**：`auto`、`lambda`、`tuple`、初始化列表 `{}`
- **替代方案**：
  - `auto` → 明确指定类型
  - `lambda` → 函数对象
  - `tuple` → 结构体
  - `{a, b}` → `make_pair(a, b)`

### 常用头文件

```cpp
#include <iostream>    // cin, cout
#include <vector>      // vector
#include <string>      // string
#include <map>         // map
#include <set>         // set
#include <queue>       // queue, priority_queue
#include <stack>       // stack
#include <algorithm>   // sort, find等
#include <numeric>     // accumulate, iota等
#include <functional>  // plus, minus, greater, less等函数对象
#include <iomanip>     // setw, setprecision
#include <sstream>     // stringstream
#include <iterator>    // back_inserter, ostream_iterator等
```
