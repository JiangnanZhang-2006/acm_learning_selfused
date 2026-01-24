# 无序容器

## unordered_map

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

## unordered_set

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

## unordered_multimap

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

## unordered_multiset

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
