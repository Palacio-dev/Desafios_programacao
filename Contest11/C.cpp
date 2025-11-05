#include <bits/stdc++.h>
using namespace std;

// Constantes e tipos
// CRÍTICO: MAX_N aumentado para 1e6+10 para caber S + T
const int MAX_N = 1e6 + 10; 
typedef long long ll;

// Variáveis globais para SA
char T[MAX_N];            
int n;                    
int RA[MAX_N], tempRA[MAX_N]; 
int SA[MAX_N], tempSA[MAX_N]; 
int c[MAX_N];  

/**
 * Funções fornecidas para Suffix Array e LCP
 * (Nenhuma modificação, exceto MAX_N)
 */

void countingSort(int k) {
    int i, sum, maxi = max(300, n); 
    fill(c, c + maxi, 0);
    for (i = 0; i < n; i++) {
        c[i + k < n ? RA[i + k] : 0]++;
    }
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) {
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    }
    for (i = 0; i < n; i++) {
        SA[i] = tempSA[i];
    }
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i]; 
    for (i = 0; i < n; i++) SA[i] = i;    
    for (k = 1; k < n; k <<= 1) {       
        countingSort(k);            
        countingSort(0);            
        tempRA[SA[0]] = r = 0;      
        for (i = 1; i < n; i++) {
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        }
        for (i = 0; i < n; i++) {  
            RA[i] = tempRA[i];
        }
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

vector<int> lcp_construction(string const& s) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[SA[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = SA[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

/**
 * Função principal para resolver o problema
 */
void solve() {
    string s1, s2;
    cin >> s1 >> s2;

    int lenS = s1.length();
    int lenT = s2.length();

    // 1. Criar string concatenada
    string U = s1 + "$" + s2 + "#";
    
    // Configura variáveis globais para constructSA
    n = U.length();
    for(int i = 0; i < n; i++) {
        T[i] = U[i];
    }

    // 2. Construir Suffix Array
    constructSA();

    // 3. Construir LCP Array
    vector<int> lcp = lcp_construction(U);

    // 4. Iterar e encontrar o LCP máximo entre S e T
    int maxLCP = 0;
    int startA = 0;
    int startC = 0;

    for (int i = 0; i < n - 1; i++) {
        // Determina o "dono" de cada sufixo adjacente
        // Dono 1: pertence a S (índice < lenS)
        // Dono 2: pertence a T (índice > lenS, pois lenS é o índice do '$')
        int owner1 = (SA[i] < lenS) ? 1 : 2;
        int owner2 = (SA[i+1] < lenS) ? 1 : 2;

        // Se os donos são diferentes, lcp[i] é um candidato
        if (owner1 != owner2) {
            if (lcp[i] > maxLCP) {
                maxLCP = lcp[i];
                
                // Armazena os índices de início corretos
                if (owner1 == 1) { // SA[i] é de S, SA[i+1] é de T
                    startA = SA[i];
                    startC = SA[i+1] - (lenS + 1); // Ajusta para o início de T
                } else { // SA[i] é de T, SA[i+1] é de S
                    startA = SA[i+1];
                    startC = SA[i] - (lenS + 1); // Ajusta para o início de T
                }
            }
        }
    }

    // 5. Imprimir a resposta
    if (maxLCP == 0) {
        cout << "0 0 0 0\n";
    } else {
        cout << startA << " " << (startA + maxLCP) << " " 
             << startC << " " << (startC + maxLCP) << "\n";
    }
}

int main() {
    solve();
}