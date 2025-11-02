#include <bits/stdc++.h>
using namespace std;
const int MAT_N = 2;
long long MOD; 


struct Matrix{
    long long mat[MAT_N][MAT_N];
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
};

Matrix multiply(const Matrix& a, const Matrix& b){
    Matrix result;
    for (int i = 0; i < MAT_N; i++){
        for (int j = 0; j < MAT_N; j++){
            for (int k = 0; k < MAT_N; k++){
                result.mat[i][j] = (result.mat[i][j] + (a.mat[i][k] * b.mat[k][j]) % MOD) % MOD;
            }
        }
    }
    return result;
}

Matrix power(Matrix base, unsigned long long exp){
    Matrix result;
    result.mat[0][0] = 1;
    result.mat[1][1] = 1;

    while (exp > 0){
        if (exp % 2 == 1){ 
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp /= 2;
    }
    return result;
}

int main() {
    unsigned long long n;
    int b;
    int caseNum = 1;
    while (cin >> n >> b and (n != 0 || b != 0)){
        MOD = b;
        Matrix T;
        T.mat[0][0] = 1; T.mat[0][1] = 1;
        T.mat[1][0] = 1; T.mat[1][1] = 0;
        Matrix T_n = power(T, n);
        long long fib_n_plus_1 = T_n.mat[0][0];
        long long ans = (2 * fib_n_plus_1 - 1 + MOD) % MOD;
        cout << "Case " << caseNum++ << ": " << n << " " << MOD << " " << ans << endl;
    }
}