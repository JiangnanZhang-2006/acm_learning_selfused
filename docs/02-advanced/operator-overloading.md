# 运算符重载

## 运算符重载基本概念

- 允许为自定义类型定义运算符的行为
- 可以重载大部分运算符（`+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, `[]`, `()` 等）
- 不能重载的运算符：`::`, `.*`, `.`, `?:`

## 时间类示例

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

## 常用运算符重载

### 算术运算符

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

### 比较运算符

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

### 下标运算符

```cpp
// 重载 []
int& operator[](int index) {
    return data[index];
}

const int& operator[](int index) const {
    return data[index];
}
```

### 函数调用运算符

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

### 自增自减运算符

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

### 赋值运算符

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

### 更多算术运算符

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

### 更多比较运算符

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

### 类型转换运算符

```cpp
// 重载类型转换运算符（转换为 double，表示距离原点的距离）
operator double() const {
    return sqrt(x * x + y * y);
}

// 使用
Point p(3, 4);
double dist = p;  // dist = 5.0（自动转换为 double）
```

### 成员访问运算符

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

### 输入输出运算符（友元函数）

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
