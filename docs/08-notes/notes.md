# 注意事项

## C++98 vs C++11

- **C++98不支持**：`auto`、`lambda`、`tuple`、初始化列表 `{}`
- **替代方案**：
  - `auto` → 明确指定类型
  - `lambda` → 函数对象
  - `tuple` → 结构体
  - `{a, b}` → `make_pair(a, b)`

## 常用头文件

```cpp
#include <iostream>    // cin, cout
#include <vector>      // vector
#include <string>      // string
#include <map>         // map
#include <set>         // set
#include <queue>       // queue, priority_queue
#include <stack>       // stack
#include <algorithm>   // sort, find等
#include <numeric>     // accumulate, iota等
#include <functional>  // plus, minus, greater, less等函数对象
#include <iomanip>     // setw, setprecision
#include <sstream>     // stringstream
#include <iterator>    // back_inserter, ostream_iterator等
```
