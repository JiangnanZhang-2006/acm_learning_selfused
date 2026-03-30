# ACM 竞赛编程环境配置

## bits/stdc++.h 支持

本项目已配置 `bits/stdc++.h` 头文件支持（适用于 clang 编译器）。

### 文件结构

```
acm/
├── include/
│   └── bits/
│       └── stdc++.h    # 自定义的 bits/stdc++.h 头文件
├── .vscode/
│   ├── c_cpp_properties.json  # IntelliSense 配置
│   └── tasks.json             # 编译任务配置
└── README.md
```

### 使用方法

#### 在 VSCode 中

1. **编译当前文件**：`Cmd + Shift + B`（选择"编译当前文件"）
2. **编译并运行**：选择任务"编译并运行当前文件"

#### 命令行编译

```bash
# 基本编译
clang++ -std=c++17 -I./include your_file.cpp -o output

# 带优化
clang++ -std=c++17 -O2 -I./include your_file.cpp -o output

# 调试模式
clang++ -std=c++17 -g -I./include your_file.cpp -o output
```

### 示例代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    cout << "Hello, Competitive Programming!" << endl;
    return 0;
}
```

### 包含的标准库

`bits/stdc++.h` 包含以下所有标准库：

- **C 标准库**：`<cmath>`, `<cstdio>`, `<cstring>`, `<ctime>` 等
- **容器**：`<vector>`, `<map>`, `<set>`, `<queue>`, `<stack>`, `<deque>` 等
- **算法**：`<algorithm>`, `<numeric>` 等
- **字符串**：`<string>`, `<sstream>` 等
- **输入输出**：`<iostream>`, `<fstream>`, `<iomanip>` 等
- **C++11/14/17/20**：`<unordered_map>`, `<tuple>`, `<optional>`, `<variant>` 等

### 注意事项

1. `bits/stdc++.h` 主要用于竞赛编程，**不建议在生产代码中使用**
2. 包含所有头文件会增加编译时间
3. 该头文件在 GCC 中是标准的，但在 clang 中需要手动创建

### 编译器版本

```bash
# 查看当前 clang 版本
clang++ --version
```

当前配置支持：
- C++17 标准
- Apple clang version 17.0.0
- ARM64 架构（M1/M2/M3 芯片）

### 故障排查

如果遇到"找不到 bits/stdc++.h"错误：

1. 确认 `include/bits/stdc++.h` 文件存在
2. 检查编译命令是否包含 `-I./include` 参数
3. 在 VSCode 中，重新加载窗口（`Cmd + Shift + P` → "Reload Window"）

### 其他配置

#### 修改 C++ 标准版本

编辑 `.vscode/tasks.json`，将 `-std=c++17` 改为：
- `-std=c++11`（C++11）
- `-std=c++14`（C++14）
- `-std=c++20`（C++20）

#### 添加编译优化

常用编译选项：
- `-O2`：标准优化
- `-O3`：最高优化
- `-g`：调试信息
- `-Wall -Wextra`：显示所有警告
