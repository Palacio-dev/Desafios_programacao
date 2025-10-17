#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Definindo um tamanho máximo para a string, conforme o slide
const int MAX_N = 100010;

// Variáveis globais extraídas da apresentação
char T[MAX_N];            // String de entrada
int n;                    // Comprimento da string de entrada
int RA[MAX_N], tempRA[MAX_N]; // Array de ranks e seu temporário
int SA[MAX_N], tempSA[MAX_N]; // Suffix Array e seu temporário
int c[MAX_N];             // Array para o counting sort

/**
 * @brief Ordena o Suffix Array (SA) usando counting sort com base nos ranks.
 * Esta função é a parte que faltava no slide. Ela ordena os sufixos
 * com base em seus segundos elementos do par de ranks (deslocados por k)
 * e armazena o resultado em tempSA.
 * @param k O deslocamento atual (2^k na iteração) para o segundo rank.
 */
void countingSort(int k) {
    int i, sum, maxi = max(300, n); // 300 é um valor seguro para ASCII
    fill(c, c + maxi, 0);

    // Conta a frequência de cada rank
    for (i = 0; i < n; i++) {
        c[i + k < n ? RA[i + k] : 0]++;
    }

    // Calcula a soma cumulativa
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }

    // Mapeia os ranks para suas posições corretas no tempSA
    for (i = 0; i < n; i++) {
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    }
    
    // Copia o resultado de volta para o SA
    for (i = 0; i < n; i++) {
        SA[i] = tempSA[i];
    }
}

/**
 * @brief Constrói o Suffix Array para a string T.
 * Implementação do algoritmo O(n log n) apresentado na aula.
 */
void constructSA() {
    int i, k, r;

    // Inicialização: ranks baseados nos valores ASCII dos caracteres
    for (i = 0; i < n; i++) RA[i] = T[i];
    // SA inicial é a ordem original dos sufixos {0, 1, 2, ..., n-1}
    for (i = 0; i < n; i++) SA[i] = i;

    // Processo iterativo, repetido log n vezes
    for (k = 1; k < n; k <<= 1) {
        // Ordena pelo segundo item do par de ranks
        countingSort(k);
        // Ordena pelo primeiro item (estável), usando o resultado anterior
        countingSort(0);
        
        // Atribui novos ranks
        tempRA[SA[0]] = r = 0; // Começa com o rank 0
        for (i = 1; i < n; i++) {
            // Compara sufixos adjacentes
            // Se o par de ranks for o mesmo, atribui o mesmo rank, senão, incrementa
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        }

        // Atualiza o array de ranks
        for (i = 0; i < n; i++) {
            RA[i] = tempRA[i];
        }

        // Otimização: se todos os ranks são únicos, o SA está completo
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

// Função auxiliar para imprimir o Suffix Array e os sufixos correspondentes
void printSuffixes() {
    cout << "----------------------------------------" << endl;
    cout << "i\tSA[i]\tSuffix" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << "\t" << SA[i] << "\t" << (T + SA[i]) << endl;
    }
    cout << "----------------------------------------" << endl;
}


int main() {
    cout << "Digite a string (sem espacos): ";
    string s;
    cin >> s;
    
    // Adiciona o caractere especial '$' no final, como nos exemplos da aula
    s += '$';
    n = s.length();
    s.copy(T, n);
    T[n] = '\0'; // Garante que a string C-style seja nula-terminada

    constructSA();

    cout << "\nSuffix Array construido para a string \"" << T << "\":" << endl;
    printSuffixes();

    return 0;
}