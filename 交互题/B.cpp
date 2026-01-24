#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

bool ask(const vector<int>& v) {
    bool is_first = true;
    for (int i : v) {
        if (is_first) {
            cout << i;
            is_first = false;
        }
        else {
            cout << ' ' << i;
        }
    }
    cout << endl;
    cout.flush();
    int ans;
    cin >> ans;
    return ans;
}

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    while (!ask(v)) {
        next_permutation(v.begin(), v.end());
    }
    return 0;
}