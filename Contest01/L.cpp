#include <iostream>
#include <vector>
using namespace std;

void read_vector(vector<int>& vet, int m){
    for (int i = 0; i < m; i++){
        int temp;
        cin >> temp;
        vet.push_back(temp);
    }
}

int sum(vector<int> & vet,int m){
    int soma = 0;
    for (int i = 0; i < m; i++){
        soma += vet[i];
    }
    return soma;
}


int main(){
    int n, m, num;
    cin >> n;
    while (n != 0){
        int soma;
        cin >> m >> num;
        vector<int> vet;
        read_vector(vet, m);
        soma = sum(vet, m);
        if (soma == num * m){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        n--;
    }

}

