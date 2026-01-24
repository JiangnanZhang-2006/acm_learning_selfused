# 关联容器

## map

```cpp
map<string, int> m;
m["key"] = value;      // 插入或修改
m.insert(make_pair("key", value));  // 插入
m.find("key");         // 查找，返回迭代器
m.count("key");        // 计数（0或1）
```

## set

```cpp
set<int> s;
s.insert(x);           // 插入
s.erase(x);            // 删除
s.find(x);             // 查找
s.count(x);            // 计数（0或1）
s.begin(); s.end();    // 迭代器
```

## multimap

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

## multiset

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
