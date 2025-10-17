#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 500010 * 2;

char T[MAX_N];            
int n;                    
int RA[MAX_N], tempRA[MAX_N]; 
int SA[MAX_N], tempSA[MAX_N]; 
int c[MAX_N];  

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
    for (i = 0; i < n; i++) RA[i] = T[i]; //inicializa o vetor RA com cada cactere com seu valor A500010;SCII
    for (i = 0; i < n; i++) SA[i] = i;    //inicializa o vetor SA com índices em ordem crescente
    for (k = 1; k < n; k <<= 1) {       //log n iteraçoes
        countingSort(k);            //ordena com base no "primeiro caractere de cada par na primeira iteração e assim por diante"
        countingSort(0);            //ordena com base no "primeiro caractere de cada par e assim por diante"    
        tempRA[SA[0]] = r = 0;      
        for (i = 1; i < n; i++) {
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        }
        for (i = 0; i < n; i++) {  //esse loop serve pra fazer o rank de novo
            RA[i] = tempRA[i];
        }
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

void printSuffixes() {
    for (int i = 1; i < n; i++) {
        cout << SA[i] << " ";
    }
    cout << endl;
}

int main(){
    string s; cin >> s; 
    s+= "$";
    n = s.length(); s.copy(T, n);
    constructSA();
    printSuffixes();
}