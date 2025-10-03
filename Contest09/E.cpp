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

void contarOcorrenciasKMP(string& texto, string& padrao) {
    int n = texto.length(); int m = padrao.length();
    vector<int> lps(m);
    calcularVetorLPS(padrao, lps);
    int i = 0; // ponteiro para o texto
    int j = 0; // ponteiro para o padrão
    int cont = 0;
    while (i < n) {
        if (padrao[j] == texto[i]){
            i++;
            j++;
        }
        if (j == m){
            cont++;
            j = lps[j - 1];
        } 
        else if (i < n and padrao[j] != texto[i]) {
            // Mismatch
            if (j != 0) {
                //Recua o ponteiro 'j' conforme o vetor lps para evitar comparar de novo.
                j = lps[j - 1];
            } else {
                //Se a incompatibilidade ocorreu no primeiro caractere do padrão.
                i++;
            }
        }
    }
    cout << cont << endl;
}

vector<int> zFunction(string s){
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            int k = i - l;
            z[i] = min(r - i + 1, z[k]);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    string texto;
    cin >> texto;
    int m = texto.length();
    vector<int> lps(m);
    calcularVetorLPS(texto, lps);
    vector<int> z = zFunction(texto);
    for(int i=0; i < z.size(); ++i){
        cout<<z[i]<<" ";
    }
    cout << endl;
    for (int i = 0; i < lps.size();i++){
        cout << lps[i] << " ";
    }
    cout << endl;
}