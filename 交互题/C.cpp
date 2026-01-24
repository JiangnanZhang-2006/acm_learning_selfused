#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void ask(int st, int ed) {
    cout << "? " << ed - st + 1 << ' ';
    for (int i = st; i <= ed; i++) {
        cout << i + 1 << ' ';
    }
    cout << endl;
    cout.flush();
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int i = 0, j = n - 1;
        int m = (i + j) / 2;
        while (i < j) {
            ask(i, m);
            int input;
            cin >> input;
            int sum = accumulate(v.begin() + i, v.begin() + m + 1, 0);
            if (input == sum) {
                i = m + 1;
            }
            else {
                j = m;
            }
            m = (i + j) / 2;
        }
        cout << "! " << i + 1 << endl;
        cout.flush();
    }
    return 0;
}