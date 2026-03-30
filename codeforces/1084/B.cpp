#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        bool sorted = true;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i > 0 && a[i] < a[i - 1]) sorted = false;
        }
        cout << (sorted ? n : 1) << endl;
    }
    return 0;
}
