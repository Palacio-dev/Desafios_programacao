#include <bits/stdc++.h>
using namespace std;

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

int main(){
    int n;
    cin >> n;
    int res = exponentMod(2,n,pow(10,9)+7);
    cout << res << endl;
    
}