#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream out("test_input.txt");
    
    int t = 1;
    int n = 100000;
    
    out << t << endl;
    out << n << endl;
    
    // 输出 0 到 99999
    for (int i = 0; i < n; i++) {
        if (i > 0) out << " ";
        out << i;
        // 每行输出一些数字，避免单行过长
        if ((i + 1) % 1000 == 0) {
            out << endl;
        }
    }
    out << endl;
    
    out.close();
    cout << "Test input generated: test_input.txt" << endl;
    cout << "Contains: t=" << t << ", n=" << n << ", numbers from 0 to " << (n-1) << endl;
    
    return 0;
}
