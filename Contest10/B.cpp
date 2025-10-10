#include <bits/stdc++.h>
using namespace std;

void stringAlignment(string& p, string& q, int n, int m) {
    vector<vector<int>> table(n + 1,vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) {table[i][0] = i;}
    for (int j = 0; j <= m; ++j) {table[0][j] = j;}
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (p[i - 1] == q[j - 1]) ? 0 : 1;
            int substitution_cost = table[i - 1][j - 1] + cost;
            int deletion_cost = table[i - 1][j] + 1; 
            int insertion_cost = table[i][j - 1] + 1; 
            table[i][j] = min({substitution_cost, deletion_cost, insertion_cost});
        }
    }
    cout << table[n][m] << endl;
}

int main() {
    int tamanhoP, tamanhoQ;
    string p, q;
    while (cin >> tamanhoP >> p) {
        cin >> tamanhoQ >> q;
        stringAlignment(p, q, tamanhoP, tamanhoQ);
    }
}