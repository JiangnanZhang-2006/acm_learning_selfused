#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string line;
    map<string, string> mp;
    while (getline(cin, line) && line != "") {
        stringstream ss(line);
        string key, value;
        ss >> value >> key;
        mp.insert(make_pair(key, value));
    }
    while (getline(cin, line) && line != "") {
        if (mp.find(line) != mp.end()) {
            cout << mp.find(line)->second << endl;
        } else {
            cout << "eh" << endl;
        }
    }
    return 0;
}