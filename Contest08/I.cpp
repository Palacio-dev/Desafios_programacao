#include <bits/stdc++.h>
using namespace std;

int main(){
    long long Vk, Jk;
    long long Vlam, Jlam;
    long long Vh, Dh, Jh;
    cin >> Vk >> Jk;
    cin >> Vlam >> Jlam;
    cin >> Vh >> Dh >> Jh;

    long long res = Vh * Dh * Jh * (Jk*Vk + Vlam*Jlam);
    cout << res << endl;


}