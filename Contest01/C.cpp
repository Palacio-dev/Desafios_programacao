#include <bits/stdc++.h> 
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int v[n];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    unordered_map <int, int> freq;
    for (int i = 0; i < k; i++){
        freq[v[i]]++;
    }
    cout << freq.size() << " ";
    for (int i = k; i < n ; i++){
        freq[v[i - k]]--;
        if (freq[v[i - k]] == 0) {
            freq.erase(v[i - k]);
        }
        freq[v[i]]++;
        cout << freq.size() << " ";
    }
    cout << endl;
}