#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

struct Matrix {
    int n;
    vector<vector<ll>> a;
    Matrix(int _n = 0): n(_n), a(_n, vector<ll>(_n, 0)){}
    static Matrix identity(int _n){
        Matrix I(_n);
        for (int i = 0; i < _n; ++i) I.a[i][i] = 1;
        return I;
    }
};

Matrix multiply(const Matrix &A, const Matrix &B){
    int n = A.n;
    Matrix R(n);
    for (int i = 0; i < n; ++i){
        const auto &Arow = A.a[i];
        auto &Rrow = R.a[i];
        for (int k = 0; k < n; ++k){
            ll aik = Arow[k];
            if (aik == 0) continue; 
            const auto &Brow = B.a[k];
            for (int j = 0; j < n; ++j){
                Rrow[j] = (Rrow[j] + aik * Brow[j]) % MOD;
            }
        }
    }
    return R;
}

Matrix power(Matrix base, ll exp){
    int n = base.n;
    Matrix res = Matrix::identity(n);
    while (exp > 0){
        if (exp & 1LL) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1LL;
    }
    return res;
}

int main(){
    int n; ll m, k;
    cin >> n >> m >> k;
    Matrix adj(n);
    for (ll i = 0; i < m; ++i){
        int u, v; cin >> u >> v;
        --u; --v;
        adj.a[u][v] = (adj.a[u][v] + 1) % MOD;
    }
    Matrix ans = power(adj, k);
    cout << ans.a[0][n - 1] % MOD << endl;
}