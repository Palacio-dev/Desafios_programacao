#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> res(n);
    long long d1 = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            d1 += a[i]; 
        } else {
            d1 -= a[i]; 
        }
    }
    res[0] = d1;
    for (int i = 1; i < n; i++) {
        res[i] = 2 * a[i - 1] - res[i - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}