#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long N, K, tot = 0, cnt = 0;
    cin >> N >> K;

    while (tot < K) {
        cnt++;
        tot += N;
        N++;
    }
    cout << (cnt == 0 ? 0 : cnt - 1) << endl;
    return 0;
}