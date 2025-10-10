#include <bits/stdc++.h>
using namespace std;

int stringAlignment(string& p, string& q) {
    int n = p.length();
    int m = q.length();
    vector<vector<int>> table(n + 1,vector<int>(m + 1, 0));
    int match_score = 5; int mismatch_score = -4; int gap_score = -7;    
    for (int i = 1; i <= n; ++i) {table[i][0] = i * gap_score;}
    for (int j = 1; j <= m; ++j) {table[0][j] = j * gap_score;}
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int score = (p[i - 1] == q[j - 1]) ? match_score : mismatch_score;
            int align_score = table[i - 1][j - 1] + score;
            int gap_p_score = table[i - 1][j] + gap_score;
            int gap_q_score = table[i][j - 1] + gap_score;
            table[i][j] = max({align_score, gap_p_score, gap_q_score});
        }
    }
    return table[n][m];
}

int main() {
    string line, query, seq;
    map<string, int> database;
    getline(cin, line); getline(cin, query); getline(cin, line);
    while (getline(cin, line)) {
        if (line.empty() or line[0] == '>'){continue;}
        seq = line;
        int score = stringAlignment(query, seq);
        database[seq] = score;
    }
    int max_score = -1;
    for (const auto& pair : database) {
        if (pair.second > max_score){
            max_score = pair.second;
        }
    }
    cout << "The query sequence is:" << endl;
    cout << query << endl << endl;
    cout << "The most similar sequences are:" << endl << endl; 
    for (const auto& pair : database) {
        if (pair.second == max_score) {
            cout << pair.first << endl;
            cout << "The similarity score is: " << pair.second << endl;
        }
    }
}