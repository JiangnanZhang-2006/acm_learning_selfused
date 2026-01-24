# 模板 (Template)

## 函数模板

- **泛型编程**：编写与类型无关的代码
- 编译器根据调用时传入的参数类型自动实例化
- 避免为不同类型重复编写相同逻辑

### 基本语法

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// 使用
int m1 = max(3, 5);           // T = int
double m2 = max(3.5, 2.1);    // T = double
```

### 多类型参数

```cpp
template <typename T, typename U>
void print_pair(T a, U b) {
    cout << a << " " << b << endl;
}

print_pair(1, "hello");       // T = int, U = const char*
print_pair(3.14, 5);          // T = double, U = int
```

### 显式指定类型

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int result = add<int>(3.5, 2.1);  // 显式指定 T = int，结果为 5
```

### 模板特化

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

## 类模板

- 定义与类型无关的类
- STL 容器都是类模板（如 `vector<T>`, `map<K, V>`）

### 类模板基本语法

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

### 类模板多类型参数

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

### 模板成员函数

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

## 模板注意事项

### C++98 限制

- 不支持 `auto` 类型推导
- 不支持变长参数模板（C++11）
- 不支持默认模板参数（部分支持）

### 常见问题

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
