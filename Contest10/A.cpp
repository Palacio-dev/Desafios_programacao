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
}

void stringAlignment(const std::string& p, const std::string& q) {
    int n = p.length();
    int m = q.length();
    vector<vector<int>> table(n + 1,vector<int>(m + 1, 0));
    int match_score = 2; int mismatch_score = -1; int gap_score = -1;    
    for (int i = 1; i <= n; ++i) {table[i][0] = i * gap_score;}
    for (int j = 1; j <= m; ++j) {table[0][j] = j * gap_score;}
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Caso 1: Alinhar P[i-1] e Q[j-1] 
            int score = (p[i - 1] == q[j - 1]) ? match_score : mismatch_score;
            int align_score = table[i - 1][j - 1] + score;
            // Caso 2: Remover P[i-1] (gap em P) 
            int gap_p_score = table[i - 1][j] + gap_score;
            // Caso 3: Remover Q[j-1] (gap em Q) 
            int gap_q_score = table[i][j - 1] + gap_score;
            // O valor da célula é o máximo das três opções 
            table[i][j] = max({align_score, gap_p_score, gap_q_score});
        }
    }
}

int main(){

}