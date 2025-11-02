#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const long long MOD = 1000000009;

void multiply(ll T[3][3], ll M[3][3]){
    long long temp[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++){
            temp[i][j] = 0;
            for (int k = 0; k < 3; k++){
                temp[i][j] = (temp[i][j] + (T[i][k] * M[k][j]) % MOD) % MOD;
            }
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            T[i][j] = temp[i][j];
        }
    }
}

void power(ll T[3][3], ll n){
    if (n == 0 || n == 1) return;
    ll M[3][3] = {{ 1, 1, 1 }, 
                   { 1, 0, 0 }, 
                   { 0, 1, 0 }};
    power(T, n / 2); multiply(T, T);
    if (n % 2 != 0) multiply(T, M);
}

ll tribonacci(ll n){
    if (n == 1) return 0;
    if (n == 2) return 1;
    if (n == 3) return 2;
    ll T[3][3] = {{ 1, 1, 1 }, 
                   { 1, 0, 0 },
                   { 0, 1, 0 }};
    power(T, n - 3);
    ll result = (2LL * T[0][0] + T[0][1]) % MOD;
    return result;
}

int main(){
    ll num;
    while (cin >> num){
        if (num == 0) break;
        cout << tribonacci(num) << endl;
    }
}