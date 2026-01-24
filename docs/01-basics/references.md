# 引用

## 基本概念

- 引用是变量的别名
- 必须在声明时初始化
- 不能重新绑定到其他变量

```cpp
int a = 10;
int& ref = a;  // ref是a的引用
ref = 20;      // a也变成20
```

## 引用作为函数参数

```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

## 引用作为返回值

```cpp
int& getMax(int& a, int& b) {
    return a > b ? a : b;
}
```
