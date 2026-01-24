# 函数对象 (Functor)

## 自定义比较函数

```cpp
struct Compare {
    bool operator()(const int& a, const int& b) {
        return a > b;  // 降序
    }
};
sort(v.begin(), v.end(), Compare());
```

## Lambda 表达式（C++11）

Lambda 表达式是一种匿名函数，可以在需要函数对象的地方直接定义，使代码更简洁。

**基本语法：**

```cpp
[捕获列表](参数列表) -> 返回类型 { 函数体 }
```

**最简单的形式：**

```cpp
// 无参数，无返回值
auto f = []() { cout << "Hello" << endl; };
f();  // 输出 Hello

// 有参数
auto add = [](int a, int b) { return a + b; };
int sum = add(3, 5);  // sum = 8

// 在算法中使用
vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
// v = {5, 4, 3, 1, 1}（降序）
```

**捕获列表：**

Lambda 可以通过捕获列表访问外部变量：

```cpp
int x = 10;
int y = 20;

// 1. [=]：按值捕获所有外部变量
auto f1 = [=]() { return x + y; };  // 捕获 x 和 y 的副本
// f1() = 30

// 2. [&]：按引用捕获所有外部变量
auto f2 = [&]() { x++; return x + y; };  // 修改原变量
// f2() = 31, x 变成 11

// 3. [x, y]：按值捕获指定变量
auto f3 = [x, y]() { return x + y; };  // 只捕获 x 和 y

// 4. [&x, y]：混合捕获（x 按引用，y 按值）
auto f4 = [&x, y]() { x++; return x + y; };

// 5. [=, &x]：按值捕获所有，但 x 按引用
auto f5 = [=, &x]() { x++; return x + y; };

// 6. [&, x]：按引用捕获所有，但 x 按值
auto f6 = [&, x]() { y++; return x + y; };
```

**在算法中使用 Lambda：**

```cpp
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 1. 使用 lambda 作为比较函数
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
// 降序排序

// 2. 使用 lambda 作为谓词（返回 bool）
int count = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// 统计偶数个数

// 3. 使用 lambda 进行转换
vector<int> result(v.size());
transform(v.begin(), v.end(), result.begin(), [](int x) { return x * 2; });
// 每个元素乘以 2

// 4. 使用 lambda 查找
auto it = find_if(v.begin(), v.end(), [](int x) { return x > 5; });
// 找到第一个大于 5 的元素

// 5. 使用 lambda 删除
v.erase(remove_if(v.begin(), v.end(), [](int x) { return x < 5; }), v.end());
// 删除所有小于 5 的元素
```

**捕获外部变量示例：**

```cpp
int threshold = 5;
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 使用外部变量 threshold
int count = count_if(v.begin(), v.end(), 
                     [threshold](int x) { return x > threshold; });
// 统计大于 threshold 的元素个数

// 修改外部变量
int sum = 0;
for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
// sum = 55（累加所有元素）
```

**返回类型：**

```cpp
// 自动推导返回类型（简单情况）
auto add = [](int a, int b) { return a + b; };

// 显式指定返回类型
auto divide = [](double a, double b) -> double {
    if (b == 0) return 0.0;
    return a / b;
};

// 复杂返回类型
auto complex = [](int x) -> pair<int, int> {
    return make_pair(x * 2, x * 3);
};
```

**Lambda vs 函数对象：**

```cpp
// 方法1：使用函数对象（C++98）
struct Compare {
    bool operator()(int a, int b) { return a > b; }
};
sort(v.begin(), v.end(), Compare());

// 方法2：使用 lambda（C++11，更简洁）
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

**常见用途：**

```cpp
// 1. 排序
vector<pair<int, string>> v = {{3, "c"}, {1, "a"}, {2, "b"}};
sort(v.begin(), v.end(), [](const pair<int, string>& a, 
                            const pair<int, string>& b) {
    return a.first < b.first;  // 按第一个元素排序
});

// 2. 查找
vector<int> v = {1, 2, 3, 4, 5};
auto it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });

// 3. 转换
vector<int> v1 = {1, 2, 3};
vector<int> v2(v1.size());
transform(v1.begin(), v1.end(), v2.begin(), 
          [](int x) { return x * x; });  // 平方

// 4. 累加
int sum = accumulate(v.begin(), v.end(), 0, 
                     [](int a, int b) { return a + b * b; });  // 平方和

// 5. 条件删除
v.erase(remove_if(v.begin(), v.end(), 
                  [](int x) { return x < 0; }), v.end());
```

**注意事项：**

- Lambda 是 C++11 特性，C++98 不支持
- 捕获列表中的变量在 lambda 创建时捕获（按值）或绑定（按引用）
- 按值捕获的变量在 lambda 内部是只读的（除非使用 `mutable`）
- 按引用捕获要注意变量的生命周期
- Lambda 可以赋值给 `auto` 变量或 `function` 对象

**C++98 替代方案：**

```cpp
// C++98：使用函数对象
struct GreaterThan {
    int threshold;
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int x) { return x > threshold; }
};

int count = count_if(v.begin(), v.end(), GreaterThan(5));
```

## functional 头文件

`<functional>` 头文件提供了许多预定义的函数对象，可以直接使用，无需自己定义。

### 算术函数对象

```cpp
#include <functional>

// 1. plus：加法
plus<int> add;
int result = add(3, 5);  // result = 8
// 等价于：int result = 3 + 5;

// 2. minus：减法
minus<int> sub;
int result2 = sub(10, 3);  // result2 = 7

// 3. multiplies：乘法
multiplies<int> mul;
int result3 = mul(4, 5);  // result3 = 20

// 4. divides：除法
divides<int> div;
int result4 = div(20, 4);  // result4 = 5

// 5. modulus：取模
modulus<int> mod;
int result5 = mod(10, 3);  // result5 = 1

// 6. negate：取反（一元操作）
negate<int> neg;
int result6 = neg(5);  // result6 = -5
```

**在算法中使用：**

```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = {4, 5, 6};
vector<int> result(3);

// 使用 transform 和 plus 进行元素相加
transform(v1.begin(), v1.end(), v2.begin(), result.begin(), plus<int>());
// result = {5, 7, 9}

// 使用 transform 和 multiplies 进行元素相乘
transform(v1.begin(), v1.end(), v2.begin(), result.begin(), multiplies<int>());
// result = {4, 10, 18}
```

#### 比较函数对象

```cpp
#include <functional>

// 1. equal_to：等于
equal_to<int> eq;
bool b1 = eq(5, 5);  // b1 = true

// 2. not_equal_to：不等于
not_equal_to<int> ne;
bool b2 = ne(5, 3);  // b2 = true

// 3. greater：大于
greater<int> gt;
bool b3 = gt(5, 3);  // b3 = true

// 4. less：小于
less<int> lt;
bool b4 = lt(3, 5);  // b4 = true

// 5. greater_equal：大于等于
greater_equal<int> ge;
bool b5 = ge(5, 5);  // b5 = true

// 6. less_equal：小于等于
less_equal<int> le;
bool b6 = le(3, 5);  // b6 = true
```

**在算法中使用：**

```cpp
vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// 使用 greater 降序排序
sort(v.begin(), v.end(), greater<int>());
// v = {9, 6, 5, 4, 3, 2, 1, 1}

// 使用 less 升序排序（默认）
sort(v.begin(), v.end(), less<int>());
// v = {1, 1, 2, 3, 4, 5, 6, 9}

// 使用 equal_to 查找相等元素
auto it = find_if(v.begin(), v.end(), bind2nd(equal_to<int>(), 5));
// 找到第一个等于 5 的元素
```

#### 逻辑函数对象

```cpp
#include <functional>

// 1. logical_and：逻辑与
logical_and<bool> land;
bool b1 = land(true, false);  // b1 = false

// 2. logical_or：逻辑或
logical_or<bool> lor;
bool b2 = lor(true, false);  // b2 = true

// 3. logical_not：逻辑非（一元操作）
logical_not<bool> lnot;
bool b3 = lnot(true);  // b3 = false
```

#### 函数适配器（C++98）

**注意：** 这些适配器在 C++11 中已弃用，推荐使用 `bind` 或 `lambda`。

```cpp
#include <functional>

// 1. bind1st：绑定第一个参数
vector<int> v = {1, 2, 3, 4, 5};
int count = count_if(v.begin(), v.end(), bind1st(less<int>(), 3));
// 计算小于 3 的元素个数（等价于 count_if(..., [](int x) { return 3 < x; })）
// count = 2（元素 1, 2）

// 2. bind2nd：绑定第二个参数
int count2 = count_if(v.begin(), v.end(), bind2nd(less<int>(), 3));
// 计算小于 3 的元素个数（等价于 count_if(..., [](int x) { return x < 3; })）
// count2 = 2（元素 1, 2）

// 3. not1：对一元谓词取反
not1(logical_not<bool>())  // 很少使用

// 4. not2：对二元谓词取反
not2(less<int>())  // 等价于 greater_equal<int>()
```

**C++11 替代方案（推荐）：**

```cpp
// 使用 lambda（C++11）
int count = count_if(v.begin(), v.end(), [](int x) { return x < 3; });

// 使用 bind（C++11）
#include <functional>
using namespace std::placeholders;
int count2 = count_if(v.begin(), v.end(), bind(less<int>(), _1, 3));
```

#### functional 使用示例

```cpp
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>

vector<int> v = {1, 2, 3, 4, 5};

// 1. 使用 plus 累加
int sum = accumulate(v.begin(), v.end(), 0, plus<int>());
// sum = 15

// 2. 使用 multiplies 累乘
int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
// product = 120

// 3. 使用 greater 降序排序
sort(v.begin(), v.end(), greater<int>());
// v = {5, 4, 3, 2, 1}

// 4. 使用 less 升序排序
sort(v.begin(), v.end(), less<int>());
// v = {1, 2, 3, 4, 5}

// 5. 使用 equal_to 统计相等元素
int count = count_if(v.begin(), v.end(), bind2nd(equal_to<int>(), 3));
// count = 1（有一个元素等于 3）
```

**常用函数对象总结：**

| 类别 | 函数对象 | 操作 | 示例 |
| ---- | -------- | ---- | ---- |
| **算术** | `plus<T>` | `a + b` | `plus<int>()(3, 5)` → 8 |
| | `minus<T>` | `a - b` | `minus<int>()(10, 3)` → 7 |
| | `multiplies<T>` | `a * b` | `multiplies<int>()(4, 5)` → 20 |
| | `divides<T>` | `a / b` | `divides<int>()(20, 4)` → 5 |
| | `modulus<T>` | `a % b` | `modulus<int>()(10, 3)` → 1 |
| | `negate<T>` | `-a` | `negate<int>()(5)` → -5 |
| **比较** | `equal_to<T>` | `a == b` | `equal_to<int>()(5, 5)` → true |
| | `not_equal_to<T>` | `a != b` | `not_equal_to<int>()(5, 3)` → true |
| | `greater<T>` | `a > b` | `greater<int>()(5, 3)` → true |
| | `less<T>` | `a < b` | `less<int>()(3, 5)` → true |
| | `greater_equal<T>` | `a >= b` | `greater_equal<int>()(5, 5)` → true |
| | `less_equal<T>` | `a <= b` | `less_equal<int>()(3, 5)` → true |
| **逻辑** | `logical_and<T>` | `a && b` | `logical_and<bool>()(true, false)` → false |
| | `logical_or<T>` | `a \|\| b` | `logical_or<bool>()(true, false)` → true |
| | `logical_not<T>` | `!a` | `logical_not<bool>()(true)` → false |
