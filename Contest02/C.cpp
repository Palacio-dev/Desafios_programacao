#include <bits/stdc++.h>
using namespace std;

bool verifica_valido(vector<char>& exp, int comeco){
    int count = 0;
    for (int i = comeco; i < exp.size(); i++){
        if (count < 0){
            return false;
        }
        if (exp[i] == '('){
            count += 1;
            continue;
        }
        else if (exp[i] == ')'){
            count -= 1;
        }
    }
    if (count == 0){
        return true;
    }
    return false;
}

void read_string(vector<char>& exp, int n){
    for (int i = 0; i < n; i++){
        char temp;
        cin >> temp;
        exp.push_back(temp);
    }
}

int main(){
    int n;
    cin >> n;
    vector<char> exp;
    bool continua = true;
    int cont = 1;
    read_string(exp, n);
    if (!verifica_valido(exp, 0)){
        while (continua){
            exp.push_back(exp[cont-1]);
            if (!verifica_valido(exp, cont)){
                cont++;
                continue;
            }
            cout << cont << endl;
            continua = false;
        }
    }
    else{
        cout << 0 << endl;
    }
}