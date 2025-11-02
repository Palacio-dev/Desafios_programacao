#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5; 
vector<int> adj[MAXN]; 

// dp[u][0] = max matching na subárvore de u, u NÃO está emparelhado (com filhos)
// dp[u][1] = max matching na subárvore de u, u ESTÁ emparelhado (com um filho)
int dp[MAXN][2];

void dfs(int u, int p){
    // Inicializa os valores de dp para o nó 'u'
    dp[u][0] = 0;
    dp[u][1] = 0;
    for (int v : adj[u]){
        if (v == p) continue; 
        // Calcula a resposta para a sub-árvore do filho 'v' primeiro
        dfs(v, u);
        // Se 'u' não vai emparelhar com filhos, 'v' pode fazer
        // o que for melhor para ele (emparelhar ou não com seus filhos).
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
    // --- Cálculo de dp[u][1] ---
    // Agora, tentamos emparelhar 'u' com cada um de seus filhos 'v'
    for (int v : adj[u]){
        if (v == p) continue;

        // 'sem_v' é o valor total de 'dp[u][0]' sem a contribuição de 'v'
        // dp[u][0] = max(dp[v][0], dp[v][1]) + (soma dos outros filhos)
        // (soma dos outros filhos) = dp[u][0] - max(dp[v][0], dp[v][1])
        int sem_v = dp[u][0] - max(dp[v][0], dp[v][1]);
        // 'com_v' é o valor se emparelharmos (u, v):
        // 1 (pela aresta u-v) 
        // + dp[v][0] (pois 'v' agora está emparelhado e não pode usar seus filhos)
        // + sem_v (os outros filhos fazem o melhor para si)
        int com_v = 1 + dp[v][0] + sem_v;
        dp[u][1] = max(dp[u][1], com_v);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // Inicia a DFS a partir da raiz (nó 1)
    // -1 indica que 1 não tem pai
    dfs(1, -1);
    //resposta final é o melhor que podemos fazer na raiz
    cout << max(dp[1][0], dp[1][1]) << '\n';
}