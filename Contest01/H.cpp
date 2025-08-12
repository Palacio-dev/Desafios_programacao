#include <iostream>
#include <string>
using namespace std;


bool eh_palindromo(string s){
    for (int i = 0; i < s.size()/2; i++){
        if (s[i] != s[s.size()-i-1]){
            return false;
        }
    }
    return true;
}

int main(){
    string s;
    cin >> s;
    if (eh_palindromo(s) and s.size() % 2 == 0){
        cout << "NO" << endl;
    }
    else if (eh_palindromo(s) and s.size() % 2 != 0){
        cout << "YES" << endl;
    }
    else{
        int cont = 0;
        for (int i = 0; i < s.size()/2; i++){
            if (cont == 2){
                break;
            }
            if (s[i] == s[s.size()-i-1]){
                continue;
            }
            cont++;        
        }
        if (cont == 1){
            cout << "YES" << endl;
        }
        else if (cont != 1) { 
            cout << "NO" << endl;
        }
    }
}
