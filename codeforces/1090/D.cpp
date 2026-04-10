#include <bits/stdc++.h>

using namespace std;

bool is_prime(unsigned long long n) {
    if (n < 2) {
        return false;
    }
    for (unsigned long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    array<unsigned long long, 20005> primes;
    primes[1] = 2;
    for (int i = 2; i <= 20000; i++) {
        unsigned long long j = primes[i - 1] + 1;
        while (!is_prime(j)) {
            j++;
        }
        primes[i] = j;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                cout << ' ';
            }
            cout << primes[i] * primes[i + 1];
        }
        cout << endl;
    }
    return 0;
}
