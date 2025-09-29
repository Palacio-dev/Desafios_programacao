#include <bits/stdc++.h>
#include <cmath>
using namespace std;

bool eh_primo(int n){
    if (n == 2 or n == 3) return true;
    for (int i = 2;i <= (sqrt(n));i++){
        if (n % i == 0) return false;
    }
    return true;
}

int main(){
    int x; cin >> x;
    if (eh_primo(x)) cout << x << endl;
    else{
        int count = x;
        while (true){
            if (!eh_primo(count)) count++;
            else{
                cout << count << endl;
                break;
            }
        }
    }
}