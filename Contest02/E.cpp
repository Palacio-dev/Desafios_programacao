#include <bits/stdc++.h>
using namespace std;

char flip(char c){
    return (c == 'H' ? 'T' : 'H');
}

int main() {
    string coins;
    cin >> coins;
    vector<string> sequence;
    sequence.push_back(coins); 
    string current_state = coins;
    while (current_state.find('H') != string::npos){
        int leftmost_h_index = -1;
        for (int i = 0; i < current_state.length(); i++){
            if (current_state[i] == 'H') {
                leftmost_h_index = i;
                break;
            }
        }
        //Virar a moeda escolhida (o 'H' mais à esquerda)
        current_state[leftmost_h_index] = 'T';
        //Virar todas as moedas à esquerda (índice 0 até i-1)
        for (int j = 0; j < leftmost_h_index; j++){
            current_state[j] = flip(current_state[j]);
        }
        //Salvar o novo estado na sequência
        sequence.push_back(current_state);
    }
    // Imprimir o resultado final
    cout << sequence.size() << '\n';
    for (const string& s : sequence){
        cout << s << '\n';
    }

}