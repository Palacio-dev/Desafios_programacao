#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    int count = 0;
    int pos_crit = INT_MAX;
    int pos = -1;

    for (int i = 0; i < n;i++){
        if (s[i] == '('){
            count++;
        }
        else{
            count--;
        }            
        if (count < pos_crit){
            pos_crit = count;
            pos = i;
        }
    }
    cout << (pos+1)%n << endl;
}