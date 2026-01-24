# 顺序容器

## vector

```cpp
vector<int> v;
v.push_back(x);        // 尾部插入
v.pop_back();          // 删除尾部元素
v.size();              // 大小
v.empty();             // 是否为空
v[i];                  // 访问元素
v.begin(); v.end();    // 迭代器
```

## deque

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

## list

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

## forward_list

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

## string

### 深拷贝特性

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

### 基本操作

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

## array

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
