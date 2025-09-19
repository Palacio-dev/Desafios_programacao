#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int x0 = 0;
int y_0 = 0; 
int d = 0;
void extendedEuclid(int a, int b) {
    if (b == 0){ 
        x0 = 1;
        y_0 = 0;
        d = a;
        return;
    }
    extendedEuclid(b, a % b);
    int x1 = y_0;
    int y1 = x0 - (a / b) * y_0;
    x0 = x1;
    y_0 = y1;
}

int main(){
    int t;
    ll n,s,k;
    cin >> t;
    while(t--){
        cin >> n >> s >> k;
        extendedEuclid(k,n);
        if (s % d != 0) {cout << -1 << endl; continue;}
        ll aux = (s/d) * x0;
        ll ans = n/d + aux;
        cout << ans << endl;
    }
}