# C++ STL 简要

本文档提供了 C++ STL（标准模板库）的简要说明和常用技巧。

## 目录

### 基础语法

- [位运算](01-basics/bitwise-operations.md) - 基本运算符和常用技巧
- [类与结构体](01-basics/class-struct.md) - 结构体、类、构造函数与析构函数
- [输入输出](01-basics/io.md) - cin/cout 加速、文件重定向、缓冲区操作、格式化输出
- [默认形参值](01-basics/default-parameters.md) - 函数参数默认值
- [引用](01-basics/references.md) - 引用的基本概念和使用
- [new 和 delete](01-basics/new-delete.md) - 动态内存分配、new/delete 运算符、内存管理

### 高级特性

- [运算符重载](02-advanced/operator-overloading.md) - 运算符重载基本概念、时间类示例、常用运算符重载
- [模板](02-advanced/templates.md) - 函数模板、类模板、模板注意事项

### STL 容器

- [容器概述](03-containers/container-overview.md) - 容器分类（按存储方式）
- [顺序容器](03-containers/sequence-containers.md) - vector, deque, list, forward_list, string, array
- [容器适配器](03-containers/container-adapters.md) - queue, stack, priority_queue
- [关联容器](03-containers/associative-containers.md) - map, set, multimap, multiset
- [无序容器](03-containers/unordered-containers.md) - unordered_map, unordered_set, unordered_multimap, unordered_multiset
- [其他容器](03-containers/other-containers.md) - tuple, pair, bitset, boost

### 算法

- [算法 (algorithm)](04-algorithms/algorithm.md) - 排序、查找、其他常用算法、集合操作、remove 和 remove_if

### 数值算法

- [数值算法 (numeric)](05-numeric/numeric.md) - 累加、前缀和、相邻差、内积、填充递增序列、最大公约数和最小公倍数

### 迭代器

- [迭代器](06-iterators/iterators.md) - 迭代器基本用法、支持的操作符、distance()、next()/prev()、逆向迭代器、只读迭代器、输入输出迭代器、迭代器适配器、C++11 范围for循环

### 函数对象

- [函数对象 (Functor)](07-functors/functors.md) - 自定义比较函数、Lambda 表达式、functional 头文件

### 注意事项

- [注意事项](08-notes/notes.md) - C++98 vs C++11、常用头文件

### 动态规划

- [动态规划](09-dynamic-programming/dynamic-programming.md) - 基本概念、一维/二维DP、背包问题、区间DP、状态压缩、优化技巧

---

## 快速导航

### 按功能分类

#### 容器选择指南

- **需要随机访问**：`vector`, `deque`, `string`, `array`
- **需要频繁插入删除**：`list`, `forward_list`
- **需要有序且快速查找**：`map`, `set`
- **只需要快速查找（无序）**：`unordered_map`, `unordered_set`
- **需要先进先出**：`queue`
- **需要后进先出**：`stack`
- **需要优先级队列**：`priority_queue`

#### 常用算法

- **排序**：`sort()`, `stable_sort()`
- **查找**：`find()`, `binary_search()`, `lower_bound()`, `upper_bound()`
- **集合操作**：`set_union()`, `set_intersection()`, `set_difference()`
- **删除**：`remove()`, `remove_if()` + `erase()`

#### 数值计算

- **累加**：`accumulate()`
- **前缀和**：`partial_sum()`
- **相邻差**：`adjacent_difference()`
- **内积**：`inner_product()`
- **填充序列**：`iota()`

#### DP 算法

- **线性 DP**：斐波那契、最大子数组和
- **区间 DP**：矩阵链乘法
- **背包问题**：0-1背包、完全背包、多重背包
- **状态压缩**：TSP、棋盘问题
- **优化技巧**：滚动数组、单调队列、斜率优化

---

## 版本说明

本文档同时支持 C++98 和 C++11 标准，对于 C++11 特性会特别标注，并提供 C++98 的替代方案。
