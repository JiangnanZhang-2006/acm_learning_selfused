#include <set>
#include <iostream>
using namespace std;

int main() {
    set<long long> s;
    s.insert(1);
    //1不算
    for (int i = 0; i < 1499; i++) {
        auto it = s.begin();
        s.insert(*it * 2);
        s.insert(*it * 3);
        s.insert(*it * 5);
        s.erase(it);
    }
    cout << "The 1500'th ugly number is " << *s.begin() << '.' << endl;
    return 0;
}