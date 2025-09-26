#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    vector<long long> nums;
    cin >> n;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    long long xor_total = 0;
    for (int i = 0; i < n; i++) {
        xor_total ^= nums[i];
    }
    long long max_valor = xor_total + 1;
    for (int i = 0; i < n; i++) {
        long long resultado_alternativo = xor_total ^ nums[i] ^ (nums[i] + 1);
        if (resultado_alternativo > max_valor) {
            max_valor = resultado_alternativo;
        }
    }
    cout << max_valor << endl;
}