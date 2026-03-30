#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    

    // bool chokutter = true;
    long long N, T;
    long long tot = 0, open_start = 0;
    cin >> N >> T;
    while (N--) {
        int temp;
        cin >> temp;
        if (temp >= open_start) {
            tot += temp - open_start;
            open_start = temp + 100;
        }
    }
    if (open_start < T) {
        tot += T - open_start;
    }
    cout << tot << endl;
    return 0;
}