#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;
    string peixe;
    for (int i = 0; i < n; i++) {
        cin >> peixe;
    }
    ll k = 0;
    if (n > 1) {
        k = floor(log2(n));
    }
    ll p_k_plus_1 = (1LL << (k + 1));
    ll y = p_k_plus_1 - n;
    ll x = (2 * n) - p_k_plus_1;
    double total_depth = (double)x * (k + 1) + (double)y * k;
    double expected_depth = total_depth / (double)n;
    double answer = expected_depth + 1.0;
    cout << fixed << setprecision(10) << answer << '\n';
}