#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int main() {
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        ll nim_sum = 0;
        for (int i = 0; i < n; i++){
            ll temp;
            cin >> temp;
            nim_sum ^= temp;
        }
        if (nim_sum == 0) cout << "second" << endl;
        else cout << "first" << endl;
    }
}
