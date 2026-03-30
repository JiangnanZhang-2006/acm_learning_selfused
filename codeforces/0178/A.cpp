#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        cout << (a / b) * (b - 1) + min(a % b, b - 1) << endl;
    }
    return 0;
    
}