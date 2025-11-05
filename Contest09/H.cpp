#include <bits/stdc++.h>
using namespace std;


void calcularVetorLPS(string& padrao, vector<int>& lps) {
    int m = padrao.length();
    lps.assign(m, 0);
    int tamanho_prefixo = 0; 
    int i = 1;
    while (i < m) {
        if (padrao[i] == padrao[tamanho_prefixo]){
            tamanho_prefixo++;
            lps[i] = tamanho_prefixo;
            i++;
        } 
        else{ 
            if (tamanho_prefixo != 0){
                tamanho_prefixo = lps[tamanho_prefixo - 1];
            } 
            else{ 
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    string texto;
    cin >> texto;
    int n = texto.length();
    vector<int> lps;
    calcularVetorLPS(texto, lps);
    vector<int> borders;
    int k = lps[n - 1];
    while (k > 0) {
        borders.push_back(k);
        k = lps[k - 1]; 
    }
    reverse(borders.begin(), borders.end());
    for (int len : borders) {
        cout << len << " ";
    }
    cout << "\n";
}