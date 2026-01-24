#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct VecBoolCmp {
    int P;
    bool operator()(const vector<bool>& a, const vector<bool>& b) const {
        for (int i = 0; i < P; i++) {
            if (a[i] != b[i]) {
                return a[i] > b[i];
            }
        }
        return false;
    }
};

int main() {
    int T, P;
    cin >> T >> P;
    vector<vector<bool>> vec(T, vector<bool>(P, true));
    cin.ignore();
    string line;
    while (getline(cin, line) && line != "") {
        stringstream ss(line);
        int t, p;
        ss >> t >> p;
        vec[t - 1][p - 1] = false;
    }
    VecBoolCmp cmp;
    cmp.P = P;
    sort(vec.begin(), vec.end(), cmp);
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    cout << vec.size() << endl;
    return 0;
}