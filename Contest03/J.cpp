#include <bits/stdc++.h>
using namespace std;

int main(){
    int t, n;
    char t1, t2,t3,t4;
    cin >> t;
    cin >> t1;
    cin >> t2;
    cin >> t3;
    cin >> t4;
    for (int i = 0; i < t;i++){
        string s;
        cin >> n;
        getline(cin, s);
        stringstream ss(s);
        if (n % 2 == 0){
            cout << "first" << endl;
        }
        else{
            cout << "second" << endl;
        }
    }
}   