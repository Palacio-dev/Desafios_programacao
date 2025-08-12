#include <bits/stdc++.h> 
using namespace std;

void operation(vector<int>& a, vector<int>& b,int num){
    auto it = lower_bound(a.begin(), a.end(), num);
    if (it != a.end() and *it == num){
        a.erase(it);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }
    for (int i = 0; i < m; i++){
        operation(a,b, b[i]);
    }
    if (!a.empty()){
        for (int i = 0; i < a.size(); i++){
            cout << a[i] << " ";
        }
    }
    cout << endl;
}