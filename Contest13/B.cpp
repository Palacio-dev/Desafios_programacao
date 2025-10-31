#include <bits/stdc++.h>
using namespace std;    


int main(){
    cout << fixed << setprecision(12);
    double d;
    cin >> d;
    if (d < 1){
        double res = sqrt(2) * d;
        cout << res << endl;
        return 0;
    }
    double res = max(sqrt(2)*d, floor(d) + 1);
    cout << res << endl;
    return 0;
}