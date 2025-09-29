#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int diameter = 0; // Variável global para armazenar a resposta

int dfs(int u, int parent){
    int longest_leg = 0;
    int second_longest_leg = 0;
    for (int v : adj[u]){
        if (v == parent) {
            continue;
        }
        int child_leg_length = 1 + dfs(v, u);
        if (child_leg_length > longest_leg){
            second_longest_leg = longest_leg;
            longest_leg = child_leg_length;
        } 
        else if (child_leg_length > second_longest_leg){
            second_longest_leg = child_leg_length;
        }
    }
    diameter = max(diameter, longest_leg + second_longest_leg);
    return longest_leg;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    cout << diameter << endl;
}