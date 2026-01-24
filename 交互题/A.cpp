#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int answer = -1;
        for (int i = 0; i <= 99; i++) {
            cout << "? " << i << endl;
            cout.flush();
            
            int t;
            cin >> t;
            
            if (t == 1) {
                answer = i;
                break;
            }
        }
        
        if (answer == -1) {
            answer = 100;
        }
        
        cout << "! " << answer << endl;
        cout.flush();
    }
    
    return 0;
}