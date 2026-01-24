# 输入输出 (cin/cout)

## 加速输入输出

```cpp
ios::sync_with_stdio(false);  // 关闭与stdio的同步
cin.tie(0);                   // 解除cin与cout的绑定
```

## 文件重定向

```cpp
// 方法1：使用ifstream
ifstream fin("input.txt");
fin >> x;
fin.close();

// 方法2：使用freopen
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
```

## 缓冲区操作

```cpp
cin.flush();    // 清空输入缓冲区
cout.flush();   // 清空输出缓冲区
cin.ignore();   // 忽略一个字符
cin.ignore(100, '\n');  // 忽略最多100个字符或直到换行
```

## 格式化输出

```cpp
cout << fixed << setprecision(2);  // 保留2位小数
cout << setw(10) << left << str;    // 左对齐，宽度10
cout << setw(10) << right << num;   // 右对齐，宽度10
cout << setfill('0') << setw(5);    // 用0填充，宽度5
```
