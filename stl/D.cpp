#include <iostream>
#include <list>
#include <unordered_map>
#include <sstream>
using namespace std;

int main() {
    int n;
    cin >> n;
    list<int> l;
    unordered_map<int, list<int>::iterator> mp;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        l.push_back(x);
        auto it = prev(l.end());
        mp[x] = it;
    }
    int m;
    cin >> m;
    cin.ignore();
    string line;
    while (m--) {
        getline(cin, line);
        stringstream ss(line);
        int cmd;
        ss >> cmd;
        if (cmd == 1) {
            int x, y;
            ss >> x >> y;
            auto it = next(mp[x]);
            auto jt = l.insert(it, y);
            mp[y] = jt;
        } else if (cmd == 2) {
            int x;
            ss >> x;
            auto it = mp[x];
            l.erase(it);
            mp.erase(x);
        }
    }
    bool is_first = true;
    for (auto i : l) {
        if (is_first) {
            cout << i;
            is_first = false;
        } else {
            cout << ' ' << i;
        }
    }
    cout << endl;
    return 0;
}