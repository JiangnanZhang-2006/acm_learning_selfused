    #include <bits/stdc++.h>

    using namespace std;

    long long binpow(long long a, long long b, long long p) {
        long long ans = 1 % p;
        long long base = a % p;
        while (b > 0) {
            if (b & 1) {
                ans = ans * base % p;
            }
            base = base * base % p;
            b >>= 1;
        }
        return ans;
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);

        long long a, b, p;
        cin >> a >> b >> p;
        cout << a << "^" << b << " mod " << p << "="<< binpow(a, b, p) << endl;
        return 0;
    }