#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;

struct Matrix {
    int n;
    vector<vector<long long>> m;

    Matrix(int n, bool identity = false) : n(n) {
        m.assign(n, vector<long long>(n, 0));
        if (identity) {
            for (int i = 0; i < n; i++) m[i][i] = 1;
        }
    }
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (m[i][k] == 0) continue; 
                for (int j = 0; j < n; j++) {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * other.m[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix power(Matrix base, long long exp) {
    Matrix result(base.n, true); 
    while (exp > 0) {
        if (exp & 1) result = result * base;
        base = base * base;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    Matrix A(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b; 
        A.m[a][b] = (A.m[a][b] + 1) % MOD;
    }
    Matrix Ak = power(A, k);
    cout << Ak.m[0][n - 1] % MOD << "\n";
    return 0;
}
