# new 和 delete

## 基本概念

`new` 和 `delete` 是 C++ 中用于动态内存分配的运算符。

- **`new`**：在堆上分配内存并返回指针
- **`delete`**：释放 `new` 分配的内存

## new 运算符

### 基本用法

```cpp
// 分配单个对象
int* p = new int;        // 分配一个 int，未初始化
int* p2 = new int(10);   // 分配一个 int，初始化为 10

// 分配数组
int* arr = new int[10];  // 分配 10 个 int 的数组

// 使用后必须释放
delete p;
delete p2;
delete[] arr;  // 注意：数组使用 delete[]
```

### 初始化

```cpp
// 单个对象初始化
int* p1 = new int;           // 未初始化（值未定义）
int* p2 = new int();         // 值初始化为 0
int* p3 = new int(42);       // 初始化为 42

// 数组初始化（C++11）
int* arr1 = new int[5];      // 未初始化
int* arr2 = new int[5]();     // 全部初始化为 0
int* arr3 = new int[5]{1, 2, 3, 4, 5};  // 列表初始化（C++11）
```

### new 失败处理

```cpp
// 方法1：检查返回值（C++98，new 失败返回 nullptr）
int* p = new int[1000000000];
if (p == nullptr) {
    // 处理分配失败
}

// 方法2：使用异常（C++11 默认行为）
try {
    int* p = new int[1000000000];
} catch (std::bad_alloc& e) {
    // 处理分配失败
}

// 方法3：使用 nothrow（不抛出异常）
int* p = new (std::nothrow) int[1000000000];
if (p == nullptr) {
    // 处理分配失败
}
```

## delete 运算符

### 基本用法

```cpp
// 释放单个对象
int* p = new int;
delete p;      // 释放单个对象
p = nullptr;   // 避免悬空指针

// 释放数组
int* arr = new int[10];
delete[] arr;  // 注意：必须使用 delete[]
arr = nullptr;
```

### 注意事项

```cpp
// 错误1：混用 new 和 delete[]
int* arr = new int[10];
delete arr;    // 错误！应该用 delete[]

// 错误2：重复释放
int* p = new int;
delete p;
delete p;      // 错误！重复释放

// 错误3：释放未分配的内存
int* p;
delete p;      // 错误！p 未指向有效内存

// 正确做法
int* p = new int;
delete p;
p = nullptr;   // 设置为 nullptr，避免悬空指针
```

## new 和 delete 的配对

```cpp
// 规则：new 对应 delete，new[] 对应 delete[]

// 单个对象
int* p = new int;
delete p;

// 数组
int* arr = new int[10];
delete[] arr;

// 多个对象
int* p1 = new int;
int* p2 = new int;
delete p1;
delete p2;
```

## 与 malloc/free 的区别

```cpp
// C 风格（不推荐在 C++ 中使用）
int* p = (int*)malloc(sizeof(int));
free(p);

// C++ 风格（推荐）
int* p = new int;
delete p;

// 区别：
// 1. new/delete 是运算符，malloc/free 是函数
// 2. new 会自动调用构造函数，malloc 不会
// 3. delete 会自动调用析构函数，free 不会
// 4. new 返回类型安全的指针，malloc 返回 void*
// 5. new 可以抛出异常，malloc 返回 nullptr
```

## 常见用法示例

### 动态分配对象

```cpp
class MyClass {
public:
    MyClass(int x) : value(x) {}
    ~MyClass() { cout << "Destructor called" << endl; }
private:
    int value;
};

// 分配对象
MyClass* obj = new MyClass(10);
delete obj;  // 自动调用析构函数
```

### 动态分配数组

```cpp
// 分配数组
int n = 10;
int* arr = new int[n];

// 使用数组
for (int i = 0; i < n; i++) {
    arr[i] = i;
}

// 释放数组
delete[] arr;
arr = nullptr;
```

### 二维数组

```cpp
// 方法1：使用一维数组模拟
int rows = 3, cols = 4;
int* arr = new int[rows * cols];
// 访问 arr[i][j] 使用 arr[i * cols + j]
delete[] arr;

// 方法2：使用指针数组
int** arr2 = new int*[rows];
for (int i = 0; i < rows; i++) {
    arr2[i] = new int[cols];
}
// 使用 arr2[i][j]
// 释放
for (int i = 0; i < rows; i++) {
    delete[] arr2[i];
}
delete[] arr2;
```

## 最佳实践

### 1. 及时释放内存

```cpp
// 好的做法
void func() {
    int* p = new int;
    // 使用 p
    delete p;
    p = nullptr;
}
```

### 2. 使用 RAII（资源获取即初始化）

```cpp
// 更好的做法：使用智能指针（C++11）
#include <memory>
void func() {
    std::unique_ptr<int> p(new int);
    // 自动释放，无需手动 delete
}
```

### 3. 避免内存泄漏

```cpp
// 错误：内存泄漏
void func() {
    int* p = new int;
    // 忘记 delete
    return;  // 内存泄漏！
}

// 正确
void func() {
    int* p = new int;
    // 使用 p
    delete p;
    p = nullptr;
}
```

### 4. 使用 nullptr（C++11）

```cpp
// C++98
int* p = NULL;

// C++11（推荐）
int* p = nullptr;
```

## 注意事项

1. **配对使用**：`new` 必须对应 `delete`，`new[]` 必须对应 `delete[]`
2. **避免重复释放**：同一块内存只能释放一次
3. **避免悬空指针**：释放后立即设置为 `nullptr`
4. **检查分配失败**：大内存分配时检查是否成功
5. **优先使用智能指针**：C++11 后推荐使用 `unique_ptr`、`shared_ptr` 等

## C++11 推荐做法

```cpp
// 不推荐：手动管理内存
int* p = new int;
delete p;

// 推荐：使用智能指针
#include <memory>
std::unique_ptr<int> p = std::make_unique<int>(10);
// 自动释放，无需手动 delete
```
