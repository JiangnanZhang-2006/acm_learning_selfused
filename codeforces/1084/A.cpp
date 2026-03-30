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
        for (int i = 0; i < n; i++) cin >> a[i];

        set<int> winners;
        for (int i = 0; i < n; i++) {
            vector<int> b = a;
            int cur = i, pre = -1;
            int tot = 0;
            for (int x : b) tot += x;
            while (tot > 0) {
                if (b[cur] > 0) {
                    b[cur]--;
                    tot--;
                    pre = cur;
                }
                cur = (cur + 1) % n;
            }
            winners.insert(pre);
        }
        cout << winners.size() << endl;
    }
    return 0;
}
