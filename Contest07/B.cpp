#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x0 = 0;
ll y_0 = 0; 
ll d = 0;
void extendedEuclid(ll a, ll b) {
    if (b == 0){ 
        x0 = 1;
        y_0 = 0;
        d = a;
        return;
    }
    extendedEuclid(b, a % b);
    ll x1 = y_0;
    ll y1 = x0 - (a / b) * y_0;
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
        ll n_prime = n/d;
        ll ans = (-aux % n_prime + n_prime) % n_prime;
        cout << ans << endl;
    }
}