# 类与结构体

## 结构体

- **默认访问权限**：`public`
- 适合存储数据

```cpp
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};
```

## 类

- **默认访问权限**：`private`
- 适合封装数据和方法

## 构造函数与析构函数

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
