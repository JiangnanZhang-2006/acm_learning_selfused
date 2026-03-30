#!/bin/bash

# 创建新的 C++ 文件并自动填充模板
# 使用方法：./new_cpp.sh 文件名

if [ -z "$1" ]; then
    echo "使用方法: ./new_cpp.sh 文件名（不需要.cpp后缀）"
    echo "示例: ./new_cpp.sh A"
    exit 1
fi

FILENAME="$1"
# 如果文件名没有 .cpp 后缀，自动添加
if [[ ! "$FILENAME" =~ \.cpp$ ]]; then
    FILENAME="${FILENAME}.cpp"
fi

# 获取脚本所在目录（即项目根目录）
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEMPLATE_FILE="$SCRIPT_DIR/template.cpp"

# 检查模板文件是否存在
if [ ! -f "$TEMPLATE_FILE" ]; then
    echo "错误：模板文件 template.cpp 不存在！"
    exit 1
fi

# 检查目标文件是否已存在
if [ -f "$FILENAME" ]; then
    read -p "文件 $FILENAME 已存在，是否覆盖？(y/N) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "操作已取消"
        exit 0
    fi
fi

# 复制模板文件
cp "$TEMPLATE_FILE" "$FILENAME"
echo "✓ 已创建文件：$FILENAME"

# 如果在 VSCode 环境中，自动打开文件
if command -v code &> /dev/null; then
    code "$FILENAME"
    echo "✓ 已在 VSCode 中打开"
fi
