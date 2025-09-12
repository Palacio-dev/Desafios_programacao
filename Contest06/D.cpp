#include <bits/stdc++.h>
#include <cmath>
using namespace std;
typedef unsigned long long ll;


ll calcula_fatorial(ll n){
    ll res = 1;
    for(int i = 2;i <= n; i++){
        res *= i;
    }
    return res;

}

int main(){
    ll a,b, resultado;
    cin >> a >> b;
    if ((a == b ) or (a > b)){
        resultado = calcula_fatorial(b);
        cout << resultado << endl;
    }
    else{
        resultado = calcula_fatorial(a);
        cout << resultado << endl;
    }
}


