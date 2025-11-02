#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;
int N; 
const int MAXN = 100; 

struct Matrix {
    array<array<long long, MAXN>, MAXN> mat{};
    void identity() {
        for (int i = 0; i < N; i++) {
            mat[i].fill(0);
        }
        for (int i = 0; i < N; i++){
            mat[i][i] = 1;
        }
    }
};

Matrix multiply(const Matrix& a, const Matrix& b){
    Matrix result; 
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            long long a_ik = a.mat[i][k];
            if (a_ik == 0) continue; 
            for (int j = 0; j < N; j++){
                result.mat[i][j] = (result.mat[i][j] + (a_ik * b.mat[k][j]) % MOD) % MOD;
            }
        }
    }
    return result;
}

Matrix power(Matrix base, long long k){
    Matrix result;
    result.identity(); 
    while (k > 0){
        if (k % 2 == 1){
            result = multiply(result, base);
        }
        base = multiply(base, base);
        k /= 2;
    }
    return result;
}

int main() {
    long long m, k;
    cin >> N >> m >> k; 
    Matrix adj;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj.mat[u - 1][v - 1]++;
    }
    Matrix result_matrix = power(adj, k);
    cout << result_matrix.mat[0][N - 1] << endl;
}