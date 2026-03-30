// G：三堆牌各 n 张，初始给出三堆顶牌之和 S；每次选择一堆弹顶，交互返回新和（非法则 -1）。
// 目标：在所有可达局面中，三堆顶牌之和的最大值。
//
// 记第 k 堆第 j 张顶牌（从上往下）相对该堆首张顶牌的差为 off[k][j]（off[k][0]=0）。
// 任意局面可独立选三堆「往下看」的深度，故最大顶和 = 初始 S + Σ_k max_j off[k][j]。
//
// 依次只对第 1、2、3 堆各弹 n-1 次：此过程中另两堆顶牌不变，故当前读入的 S 与本轮 preS 之差
// 即为该堆当前顶相对本轮首张顶的累积偏移；对内层每次更新取 max 即得该堆的 max_j off[k][j]。
// 操作次数 3(n-1) ≤ 3n。

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, S, preS, maxS, delta[4];
    fill(begin(delta), end(delta), 0);

    cin >> n >> S;
    maxS = S;  // 答案累加：初始顶和 + 三堆各自「相对首张顶」的最大增益

    for (int stackName = 1; stackName <= 3; stackName++) {
        preS = S;  // 开始处理本堆时的三堆顶和；内层固定不变，使 S-preS 为相对首张顶的累积差
        for (int i = 0; i < n - 1; i++) {
            cout << stackName << endl;  // 交互须立即刷新；endl 含 flush
            cin >> S;
            delta[stackName] = max(delta[stackName], S - preS);
        }
        maxS += delta[stackName];
    }

    cout << "! " << maxS << endl;
}
