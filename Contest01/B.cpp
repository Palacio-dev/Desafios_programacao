#include <bits/stdc++.h> 
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> A(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> A[i];
    } 
    unordered_map<long long, long long> freq;
    long long ans = 0;

    for (int j = 1; j <= n; j++) {
        long long target = j - A[j];
        if (freq.count(target)) {
            ans += freq[target];
        }
        freq[j + A[j]]++;
    }
    cout << ans << "\n";
}