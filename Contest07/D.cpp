#include <bits/stdc++.h>
using namespace std;

// calculates x^y % n
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

// int x0, y0, d;
// // store x0, y0, and d as global variables
// void extendedEuclid(int a, int b) {

//     if (b == 0) { 
//         x0 = 1; y0 = 0; d = a; return; }
//     // base case

//     extendedEuclid(b, a % b);
//     // similar as the original gcd

//     int x1 = y0;
//     int y1 = x0 - (a / b) * y0;
//     x0 = x1;
//     y0 = y1;
// }

int gcd(int a , int b){return b == 0 ? a : gcd (b, a % b);}

int main(){
    long long n,m;
    cin >> n >> m;
    long long cntN[5], cntM[5];
    for (int r = 0; r < 5; ++r) {
        if (r == 0){
            cntN[r] = n/5;
            cntM[r] = m/5;
        } 
        else{
            if (n % 5 >= r) cntN[r] = n/5 + 1;
            else cntN[r] = n/5;
            if (m % 5 >= r) cntM[r] = m/5 + 1;
            else cntM[r] = m/5;
        }
    }
    long long ans = 0;
    ans += cntN[0] * cntM[0];
    ans += cntN[1] * cntM[4];
    ans += cntN[2] * cntM[3];
    ans += cntN[3] * cntM[2];
    ans += cntN[4] * cntM[1];
    cout << ans << endl;
}

