#include <bits/stdc++.h>
using namespace std;

int main(){
    int Vr, Vl, Vd, Vm, n;
    cin >> Vr >> Vl >> Vd >> Vm >> n;
    if (Vr == 0 and Vl == 0 and Vd == 0 and Vm == 0 and n == 0){
        cout << "sem vencedores" << endl;
    }
    else{
        int votos_totais = Vr + Vl + Vd + Vm + n;
        int metade_totais;
        bool nenhuma_tartaruga = true;
        if (votos_totais % 2 == 0){
            metade_totais = votos_totais/2;
        }
        else{
            metade_totais = votos_totais/2;
        }
        if (Vd + n > metade_totais){
            cout << "Donatello" << endl;
            nenhuma_tartaruga = false;
        }
        if (Vl + n > metade_totais){
            cout << "Leonardo" << endl;
            nenhuma_tartaruga = false;
        }
        if (Vm + n > metade_totais){
            cout << "Michelangelo" << endl;
            nenhuma_tartaruga = false;
        }
        if (Vr + n > metade_totais){
            cout << "Rafael" << endl;
            nenhuma_tartaruga = false;
        }
        if (nenhuma_tartaruga){
            cout << "sem vencedores" << endl;
        }
    }
}