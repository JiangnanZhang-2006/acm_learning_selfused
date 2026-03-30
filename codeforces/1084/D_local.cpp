#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];

        int Lm = y - x;

        // min of M and its position
        int mn = p[x], mnpos = x;
        for (int i = x + 1; i < y; i++)
            if (p[i] < mn) { mn = p[i]; mnpos = i; }

        // C = L + R (invariant sequence)
        vector<int> C;
        for (int i = 0; i < x; i++) C.push_back(p[i]);
        for (int i = y; i < n; i++) C.push_back(p[i]);

        // s = longest prefix of C with all elements < mn
        int s = 0;
        while (s < (int)C.size() && C[s] < mn) s++;

        // output = C[0..s-1] + M*(starting at mn) + C[s..end]
        vector<int> res;
        for (int i = 0; i < s; i++) res.push_back(C[i]);
        for (int i = 0; i < Lm; i++) res.push_back(p[x + (mnpos - x + i) % Lm]);
        for (int i = s; i < (int)C.size(); i++) res.push_back(C[i]);

        for (int i = 0; i < n; i++)
            cout << res[i] << " \n"[i == n - 1];
    }
    return 0;
}
