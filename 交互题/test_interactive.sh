#!/bin/bash

# 编译测试程序
g++ -o test_D test_D.cpp -std=c++17 -O2
g++ -o D D.cpp -std=c++17 -O2

# 生成测试输入
echo "1" > test_input.txt
echo "100000" >> test_input.txt
for i in {0..99999}; do
    if [ $i -gt 0 ]; then
        echo -n " " >> test_input.txt
    fi
    echo -n "$i" >> test_input.txt
    # 每1000个数字换行，避免单行过长
    if [ $((i % 1000)) -eq 999 ]; then
        echo "" >> test_input.txt
    fi
done
echo "" >> test_input.txt

# 运行测试（使用管道连接两个程序）
time cat test_input.txt | ./D | ./test_D

echo ""
echo "Test completed!"
