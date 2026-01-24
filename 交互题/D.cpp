#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAX_SIZE = 300000;  // 数组大小，根据 n <= 100000，MEX 通常不会超过 200000

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        unordered_set<long long> s;  // 存储所有数字
        vector<bool> exists(MAX_SIZE, false);  // 数组记录小数字是否存在，O(1) 访问
        
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;
            s.insert(x);
            if (x < MAX_SIZE) {
                exists[x] = true;
            }
        }

        // 初始计算 MEX：优先使用数组（O(1)），超出范围再用 unordered_set
        long long mex = 0;
        while (mex < MAX_SIZE && exists[mex]) {
            mex++;
        }
        if (mex >= MAX_SIZE) {
            while (s.count(mex)) {
                mex++;
            }
        }
        
        while (true) {
            cout << mex << endl;
            cout.flush();
            s.insert(mex);
            if (mex < MAX_SIZE) {
                exists[mex] = true;
            }
            
            // 添加 mex 后，从 mex+1 开始检查
            mex++;
            if (mex < MAX_SIZE) {
                while (mex < MAX_SIZE && exists[mex]) {
                    mex++;
                }
                if (mex >= MAX_SIZE) {
                    while (s.count(mex)) {
                        mex++;
                    }
                }
            } else {
                while (s.count(mex)) {
                    mex++;
                }
            }
            
            long long y;
            cin >> y;
            
            if (y == -1) {
                break;
            } else if (y == -2) {
                return 0;
            } else {
                s.erase(y);
                if (y < MAX_SIZE) {
                    exists[y] = false;
                }
                
                if (y < mex) {
                    // y 被移除后，MEX 至少是 y（因为 y 不在集合中了）
                    // 优化：如果 y 很大或接近 mex，直接设置 MEX = y
                    // 否则，只检查较小的范围（最多检查 1000 个数字）
                    if (y < MAX_SIZE) {
                        if (y > 1000 || mex - y < 100) {
                            // y 很大或接近 mex，直接设置 MEX = y
                            mex = y;
                        } else {
                            // y 较小，从 0 开始检查，但最多检查到 y
                            mex = 0;
                            while (mex < y && exists[mex]) {
                                mex++;
                            }
                            if (mex >= y) {
                                mex = y;
                            }
                        }
                    } else {
                        // y 超出数组范围，检查数组内的数字
                        mex = 0;
                        while (mex < MAX_SIZE && exists[mex]) {
                            mex++;
                        }
                        if (mex >= MAX_SIZE) {
                            mex = y;
                        }
                    }
                }
            }
        }
    }
    return 0;
}