#include <bits/stdc++.h>
using namespace std;

void longestCommonSubsequence(string& p,string& q) {
    int n = p.length();
    int m = q.length();
    vector<vector<int>> table(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i - 1] == q[j - 1]){ table[i][j] = table[i - 1][j - 1] + 1;} 
            else{table[i][j] = max(table[i - 1][j], table[i][j - 1]);}
        }
    }
    cout << table[n][m] << endl;
}

int main(){
    string p,q;
    while (getline(cin, p) and getline(cin, q)) {
        longestCommonSubsequence(p, q);
    }
}