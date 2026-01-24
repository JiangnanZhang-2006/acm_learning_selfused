#!/usr/bin/env python3
import subprocess
import sys
import time

def generate_input():
    """生成测试输入"""
    lines = []
    lines.append("1")  # t = 1
    lines.append("100000")  # n = 100000
    # 生成 0 到 99999
    numbers = [str(i) for i in range(100000)]
    lines.append(" ".join(numbers))
    return "\n".join(lines) + "\n"

def simulate_bob(s, last_added, move_count, max_moves):
    """模拟鲍勃的策略：移除一个小于 last_added 的数字"""
    if move_count >= max_moves:
        return -1
    
    # 找到小于 last_added 的最大数字
    to_remove = -1
    for num in sorted(s):
        if num < last_added:
            to_remove = num
        else:
            break
    
    if to_remove != -1:
        s.remove(to_remove)
        return to_remove
    else:
        return -1

def main():
    # 生成输入
    input_data = generate_input()
    
    # 启动程序
    print("Starting interactive test...")
    print(f"Input size: {len(input_data)} bytes")
    
    process = subprocess.Popen(
        ["./D"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    
    # 发送输入
    process.stdin.write(input_data)
    process.stdin.flush()
    
    # 模拟交互
    s = set(range(100000))
    move_count = 0
    last_added = -1
    max_moves = 2 * 100000 + 1
    
    start_time = time.time()
    
    try:
        while move_count < max_moves:
            # 读取爱丽丝的操作
            line = process.stdout.readline()
            if not line:
                break
            
            x = int(line.strip())
            
            if x in s:
                # 非法操作
                process.stdin.write("-2\n")
                process.stdin.flush()
                print(f"Error: Invalid move - {x} already in set")
                break
            
            s.add(x)
            last_added = x
            move_count += 1
            
            # 鲍勃的操作
            bob_move = simulate_bob(s, last_added, move_count, max_moves)
            process.stdin.write(f"{bob_move}\n")
            process.stdin.flush()
            
            if bob_move == -1:
                # 游戏结束
                break
            
            move_count += 1
            
            if move_count % 10000 == 0:
                elapsed = time.time() - start_time
                print(f"Progress: {move_count} moves, {elapsed:.2f}s elapsed")
        
        elapsed = time.time() - start_time
        print(f"\nTest completed in {elapsed:.2f} seconds")
        print(f"Total moves: {move_count}")
        
        # 计算最终 MEX
        mex = 0
        while mex in s:
            mex += 1
        print(f"Final MEX: {mex}")
        print(f"Final set size: {len(s)}")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        process.terminate()
        process.wait()

if __name__ == "__main__":
    main()
