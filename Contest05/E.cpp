#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


int fatorial(int n) {
    if (n == 0 or n == 1) return 1;
    int res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

ll calcularCombinacoes(int n, int r) {
    if (r < 0 || r > n)  return 0;
    if (r > n / 2)  r = n - r;
    return fatorial(n) / (fatorial(r) * fatorial(n - r));
}

int main(){
    int t;
    cin >> t;
    double gamesA;
    double pA;
    while(t--){
        cin >> gamesA >> pA;
        int total_jogos = 2 * gamesA -1;
        ld q = 1.0L - pA;       //probabilidade de B ganhar
        ld comb = 1.0L;         
        ld p_pow = 1.0L;
        ld q_pow = pow(q,total_jogos);
        ld ans = 0.0L;

        for (int i = 0; i <= total_jogos; ++i) {
            if (i >= gamesA) ans += comb * p_pow * q_pow;
            // atualiza para o próximo i:
            // comb_{i+1} = comb_i * (trials - i) / (i + 1)
            if (i < total_jogos) {
                comb = comb * (ld)(total_jogos - i) / (i + 1);
                p_pow *= pA;
                // q != 0 aqui (já tratamos p >= 1), então divisão é segura
                q_pow /= q;
            }
        }
        // correções numéricas pequenas
        if (ans < 0.0L) ans = 0.0L;
        if (ans > 1.0L) ans = 1.0L;
        cout << (double)ans << endl;
    }
}