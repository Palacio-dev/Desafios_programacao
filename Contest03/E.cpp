#include <bits/stdc++.h>
using namespace std;

int Tribonacci(int n){
    int first = 0;
    int second = 1;
    int third = 2;
    if (n == 1){
        return 0;
    }
    if (n == 2){
        return 1;
    }
    if (n == 3){
         return 2;
    }
    int tribo_number = 0;
    for (int i = 3; i < n; i++){
        tribo_number = first + second + third;
        first = second;
        second = third;
        third = tribo_number;
    }
    return tribo_number % 1000000009;
}

int main(){
    int temp;
    for (int i = 0; i < 400;i++){
        cin >> temp;
        if (temp == 0){
            break;
        }
        cout << Tribonacci(temp) << endl;
    }
}