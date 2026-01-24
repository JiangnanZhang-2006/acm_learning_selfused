#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<int> v(N);
        vector<int> v2(N);
        vector<int> ans(N);
        iota(v.begin(), v.end(), 0);
        for (int i = 1; i < N; i++) {
            cin >> v2[i];
        }
        for (int i = N - 1; i >= 0; i--) {
            ans[i] = v[v2[i]];
            v.erase(next(v.begin(), v2[i]));
        }
        for (int i = 0; i < N; i++) {
            cout << ans[i] + 1 << endl;
        }
    }
    return 0;
}
