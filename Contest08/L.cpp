#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    vector<int> nums;
    cin >> n;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    sort(nums.begin(), nums.end());
    int quant_tesouros = n/2;
    int soma = 0;
    for (int i = 0; i < quant_tesouros; i++) {
        soma += nums[n - 1 - i];
    }
    cout << soma << endl;

}