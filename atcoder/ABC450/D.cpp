#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> vec(n);
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        vec[i] = a % k % k;
    }
    sort(vec.begin(), vec.end());

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    long long max_gap = 0;
    for (int i = 0; i + 1 < n; i++)
        max_gap = max(max_gap, vec[i + 1] - vec[i]);
    max_gap = max(max_gap, vec[0] + k - vec[n - 1]);

    cout << k - max_gap << '\n';
    return 0;
}