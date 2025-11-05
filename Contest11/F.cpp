#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 * 2;
typedef long long ll;

char T[MAX_N];            
int n;                    
int RA[MAX_N], tempRA[MAX_N]; 
int SA[MAX_N], tempSA[MAX_N]; 
int c[MAX_N];  



void countingSort(int k) {
    int i, sum, maxi = max(300, n); 
    fill(c, c + maxi, 0);
    for (i = 0; i < n; i++) {
        c[i + k < n ? RA[i + k] : 0]++;
    }
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) {
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    }
    for (i = 0; i < n; i++) {
        SA[i] = tempSA[i];
    }
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i]; 
    for (i = 0; i < n; i++) SA[i] = i;    
    for (k = 1; k < n; k <<= 1) {       
        countingSort(k);            
        countingSort(0);            
        tempRA[SA[0]] = r = 0;      
        for (i = 1; i < n; i++) {
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        }
        for (i = 0; i < n; i++) {  
            RA[i] = tempRA[i];
        }
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

vector<int> lcp_construction(string const& s) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[SA[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = SA[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}

void solve() {
    string s;
    cin >> s;
    n = s.length();
    for(int i = 0; i < n; i++) {
        T[i] = s[i];
    }
    constructSA();
    vector<int> lcp = lcp_construction(s);
    int maxLCP = 0;
    int startIndex = -1;
    for (int i = 0; i < n - 1; i++) {
        if (lcp[i] > maxLCP) {
            maxLCP = lcp[i];
            startIndex = SA[i]; 
        }
    }
    if (maxLCP == 0) {
        cout << "-1\n";
    } else {
        cout << s.substr(startIndex, maxLCP) << "\n";
    }
}

int main() {
    solve();
}