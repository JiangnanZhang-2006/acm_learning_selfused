#include <iostream>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

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
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        set<long long> s;
        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;
            s.insert(x);
        }
        
        int move_count = 0;
        long long last_added = -1;
        const int MAX_MOVES = 2 * n + 1;
        
        while (move_count < MAX_MOVES) {
            // 读取爱丽丝的操作
            long long x;
            if (!(cin >> x)) {
                break;
            }
            
            if (s.count(x)) {
                cerr << "Error: " << x << " already in set" << endl;
                cout << -2 << endl;
                cout.flush();
                return 0;
            }
            
            s.insert(x);
            last_added = x;
            move_count++;
            
            // 鲍勃的策略：移除小于 last_added 的最大数字
            long long to_remove = -1;
            for (auto it = s.rbegin(); it != s.rend(); ++it) {
                if (*it < last_added) {
                    to_remove = *it;
                    break;
                }
            }
            
            if (to_remove != -1 && move_count < MAX_MOVES) {
                s.erase(to_remove);
                cout << to_remove << endl;
                cout.flush();
                move_count++;
            } else {
                cout << -1 << endl;
                cout.flush();
                break;
            }
        }
        
        long long final_mex = getMEX(s);
        cerr << "Final MEX: " << final_mex << endl;
        cerr << "Moves: " << move_count << endl;
    }
    
    return 0;
}
