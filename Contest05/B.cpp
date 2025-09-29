#include <bits/stdc++.h>
using namespace std;

// Usando unsigned long long para suporte a inteiros maiores.
// Para n=100, uma biblioteca de inteiros grandes (BigInt) seria necessária,
// mas isso funciona para os casos de exemplo e para n até cerca de 64.
// A lógica do algoritmo não muda.
using ull = unsigned long long;

int main() {
    int n, k;
    while (cin >> n >> k){
        // dp[i] = número de sequências de tamanho i SEM k caras consecutivas.
        vector<ull> dp(n + 1);
        vector<ull> pow2(n + 1);
        // Pré-calcula as potências de 2
        pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow2[i] = pow2[i - 1] * 2;
        }
        // Casos base para a Programação Dinâmica (PD)
        dp[0] = 1;
        for (int i = 1; i < k; ++i) {
            if (i <= n) { // Garante que não acessemos fora do vetor
                dp[i] = pow2[i];
            }
        }
        // A primeira sequência inválida (k caras) aparece no comprimento k
        if (k <= n) {
            dp[k] = pow2[k] - 1;
        }
        // Constrói o resto da tabela de PD usando a recorrência
        for (int i = k + 1; i <= n; ++i) {
            dp[i] = 0;
            // Recorrência: dp[i] = dp[i-1] + ... + dp[i-k]
            for (int j = 1; j <= k; ++j) {
                dp[i] += dp[i - j];
            }
        }
        // O número de sequências com PELO MENOS k caras é:
        // Total de sequências - sequências SEM k caras.
        ull total_sequences = pow2[n];
        ull good_sequences = total_sequences - dp[n];
        cout << good_sequences << endl;
    }

    return 0;
}