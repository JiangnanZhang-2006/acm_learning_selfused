# 算法 (algorithm)

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

