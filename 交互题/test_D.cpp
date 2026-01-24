#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

// 计算 MEX
long long getMEX(const set<long long>& s) {
    long long mex = 0;
    for (long long x : s) {
        if (x == mex) {
            mex++;
        } else if (x > mex) {
            break;
        }
    }
    return mex;
}

int main() {
    // 生成测试数据
    int t = 1;
    int n = 100000;
    
    cout << t << endl;
    cout << n << endl;
    
    // 输出 0 到 99999
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << i;
    }
    cout << endl;
    cout.flush();
    
    // 模拟交互过程
    set<long long> s;
    for (int i = 0; i < n; i++) {
        s.insert(i);
    }
    
    int move_count = 0;
    long long last_added = -1;
    
    while (move_count < 2 * n + 1) {
        // 读取爱丽丝的操作
        long long x;
        if (!(cin >> x)) {
            break;
        }
        
        if (s.count(x)) {
            // 非法操作
            cout << -2 << endl;
            cout.flush();
            return 0;
        }
        
        s.insert(x);
        last_added = x;
        move_count++;
        
        // 鲍勃的策略：移除一个小于 last_added 的数字（如果存在）
        long long to_remove = -1;
        for (long long num : s) {
            if (num < last_added) {
                to_remove = num;
                break;
            }
        }
        
        if (to_remove != -1 && move_count < 2 * n + 1) {
            s.erase(to_remove);
            cout << to_remove << endl;
            cout.flush();
            move_count++;
        } else {
            // 鲍勃无法操作，游戏结束
            cout << -1 << endl;
            cout.flush();
            break;
        }
    }
    
    // 输出最终结果
    long long final_mex = getMEX(s);
    cerr << "Final MEX: " << final_mex << endl;
    cerr << "Final set size: " << s.size() << endl;
    
    return 0;
}
