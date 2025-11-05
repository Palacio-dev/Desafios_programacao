#include <bits/stdc++.h>
using namespace std;

// calcula x^y % n
int exponentMod(int x, int y, int n) {

    // base cases
    if (y == 0) return 1;
    if (x == 0) return 0;

    // y is even
    long v;
    if (y % 2 == 0) {
        v = exponentMod(x, y / 2, n);
        v = (v * v) % n;
    }

    // y is odd
    else {
        v = x % n;
        v = (v * exponentMod(x, y - 1, n)) % n;
    }

    return (int)((v + n) % n);
}

int x0, y0, d;
// store x0, y0, and d as global variables
void extendedEuclid(int a, int b) {

    if (b == 0) { 
        x0 = 1; y0 = 0; d = a; return; }
    // base case

    extendedEuclid(b, a % b);
    // similar as the original gcd

    int x1 = y0;
    int y1 = x0 - (a / b) * y0;
    x0 = x1;
    y0 = y1;
}

int gcd(int a , int b){return b == 0 ? a : gcd (b, a % b);}

int main(){
    long long X, K, D;
    cin >> X >> K >> D;
    X = abs(X);
    long long n_min = X / D;
    if (K <= n_min) {
        cout << X - K * D << endl;
    } 
    else {
        long long K_rem = K - n_min;
        long long pos1 = X % D;
        if (K_rem % 2 == 0) {
            cout << pos1 << endl;
        } 
        else {
            cout << abs(pos1 - D) << endl;
        }
    }
}