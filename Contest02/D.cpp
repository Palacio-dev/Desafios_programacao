#include <bits/stdc++.h>
using namespace std;

int soma_extremos(vector<long long>& nums, int pos){
    int receita = nums[pos] + nums[nums.size() - pos-1];
    return receita;
}

bool ta_no_intervalo(int soma, int min, int max){
    if (soma <= max  and soma >= min){
        return true;
    }
    return false;
}

int main(){
    long long n, l;
    vector<long long> nums;
    vector<long long> ordenado;
    cin >> n >> l;
    long long menosL = -1 * l;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    sort(nums.begin(), nums.end());
    long long soma_temp;
    long long receita = 0;
    bool da_pra_somar = true;
    soma_temp = soma_extremos(nums, 0);
    if (!ta_no_intervalo(soma_temp, menosL, l-1)){
        cout << "N" << endl;
    }
    else{
        ordenado.push_back(nums[0]);
        ordenado.push_back(nums[nums.size() -1]);
        receita += soma_temp;
        for (int i = 1; i < n-1; i++){
            int temp1 = receita + nums[i];
            int temp2 = receita + nums[nums.size() - i ];
            if (ta_no_intervalo(temp1, menosL, l -1)){
                receita += nums[i];
                ordenado.push_back(nums[i]);
                continue;
            }
            else if (ta_no_intervalo(temp2, menosL, l -1)){
                receita += nums[nums.size() - i ];
                ordenado.push_back(nums[nums.size()-i-1]);
                continue;
            }
            da_pra_somar = false;
            break;
        }
    
        if (da_pra_somar){
            cout << "S" << endl;
            for (int i = 0; i < n;i++){
                cout << ordenado[i] << " ";
            }
        }
        else{
            cout << "N" << endl;
        }
    }
}