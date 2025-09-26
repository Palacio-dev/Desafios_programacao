#include <bits/stdc++.h>
using namespace std;
#include <utility> // Para std::pair

// Variáveis globais para a função f(x), conforme o problema UVa 350
int Z, I, M;

// A função f(x) que gera o próximo número na sequência.
// f(x) = (Z*x + I) % M
int f(int x) {
    return (1LL * Z * x + I) % M;
}

// Implementação do Algoritmo de Floyd para Encontrar Ciclos
// Baseado no código do slide [cite: 158]
std::pair<int, int> floydCycleFinding(int x0) {
    // Fase 1: Encontrar o ponto de encontro k*lambda [cite: 158]
    // A tartaruga anda 1 passo, a lebre anda 2.
    int tortoise = f(x0);
    int hare = f(f(x0));
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    } 

    // Fase 2: Encontrar o início do ciclo (mu) 
    // A lebre volta ao início, e ambas andam na mesma velocidade.
    int mu = 0;
    hare = x0;
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    } 

    // Fase 3: Encontrar o comprimento do ciclo (lambda) [cite: 163]
    // A tartaruga fica parada no início do ciclo, a lebre dá uma volta.
    int lambda = 1;
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        lambda++;
    } 

    return std::pair<int, int>(mu, lambda);
}

int main() {
    // --- Exemplo 1 do Slide --- [cite: 54]
    Z = 7;
    I = 5;
    M = 12;
    int L1 = 4;
    cout << "Exemplo 1: Z=7, I=5, M=12, L=4" << std::endl;
    std::pair<int, int> result1 = floydCycleFinding(L1);
    // Resultado esperado: mu = 0, lambda = 6 [cite: 59]
    std::cout << "Resultado: mu = " << result1.first << ", lambda = " << result1.second << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // --- Exemplo 2 do Slide --- [cite: 70]
    Z = 3;
    I = 1;
    M = 4;
    int L2 = 7;
    cout << "Exemplo 2: Z=3, I=1, M=4, L=7" << std::endl;
    std::pair<int, int> result2 = floydCycleFinding(L2);
    // Resultado esperado: mu = 1, lambda = 2 
    std::cout << "Resultado: mu = " << result2.first << ", lambda = " << result2.second << endl;
}