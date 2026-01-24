#include <iostream>
#include <vector>

using namespace std;

bool ask(int num) {
    cout << num << endl;
    cout.flush();
    string ans;
    cin >> ans;
    return ans == "yes";
}

int main() {
    int cnt = 0;
    vector<int> v = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int i : v) {
        if (ask(i)) {
            cnt++;
            if (cnt == 2) {
                break;
            }
            if (i < 10) {
                if (ask(i * i)) {
                    cnt++;
                    break;
                }
            }
            
        }
    }
    cout << (cnt == 2 ? "composite" : "prime") << endl;
    cout.flush();
    return 0;
}