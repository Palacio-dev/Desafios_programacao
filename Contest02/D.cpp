#include <bits/stdc++.h>
using namespace std;

inline bool ta_no_intervalo(long long soma, long long lo, long long hi){
    return (soma >= lo && soma <= hi);
}

int main(){
    long long n, L;
    cin >> n >> L;
    vector<long long> nums(n);
    for (auto &x : nums) cin >> x;
    long long lo = -L, hi = L - 1;

    sort(nums.begin(), nums.end());               
    vector<long long> ordenado; ordenado.reserve(n);

    long long receita = 0;
    int l = 0, r = (int)n - 1;

    auto cabe = [&](long long x){ return ta_no_intervalo(receita + x, lo, hi); };

    while (l <= r) {
        bool moveu = false;
        if (receita >= 0) {
            if (cabe(nums[l])){ 
                receita += nums[l]; 
                ordenado.push_back(nums[l]); 
                l++; 
                moveu = true; 
            }
            else if (cabe(nums[r])){ 
                receita += nums[r]; 
                ordenado.push_back(nums[r]); 
                r--; 
                moveu = true;
            }
        } 
        else{
            if (cabe(nums[r])){ 
                receita += nums[r];
                ordenado.push_back(nums[r]); 
                r--; 
                moveu = true; 
            }
            else if (cabe(nums[l])){ 
                receita += nums[l]; 
                ordenado.push_back(nums[l]); 
                l++; 
                moveu = true; 
            }
        }
        if (!moveu){
            cout << "N\n";
            return 0;
        }  
    }

    cout << "S" << endl;;
    for (int i = 0; i < n; i++){
        if (i) cout << ' ';
        cout << ordenado[i];
    }
    cout << endl;
    return 0;
}
