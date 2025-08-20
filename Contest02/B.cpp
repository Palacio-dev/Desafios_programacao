#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    int seq = 1;
    int seq_max = 1;
    vector<int> seqs;
    int primeiro_dia = nums[0];
    for (int i = 1; i < n; i++){
        if (nums[i] == nums[i-1] + 1){
            seq += 1;
        }
        else{
            if (seq > seq_max){
                seq_max = seq;
            }
            seq = 1;
            primeiro_dia = nums[i];
        }
    }
    if (seq > seq_max){
        seq_max = seq;
    }
    cout << seq_max << endl;
}