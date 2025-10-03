#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef long long ll;
const ll MOD = 10e9+7;



// Fills the lps array for the given pattern pat[0..M-1]
void computeLPSArray(char* P, int M, int* lps) {
    // Length of the previous longest prefix suffix
    int len = 0;
    lps[0] = 0; // lps[0] is always 0

    // The loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else { // (P[i] != P[len])
            if (len != 0) {
                len = lps[len - 1];
            } else { // if (len == 0)
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of P in T
void KMPSearch(char* P, char* T) {
    int M = strlen(P);
    int N = strlen(T);

    // Create lps[] that will hold the longest prefix suffix values for the pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(P, M, lps);

    int i = 0; // index for T
    int j = 0; // index for P
    while (i < N) {
        if (P[j] == T[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found pattern at index %d \n", i - j);
            j = lps[j - 1];
        } else if (i < N && P[j] != T[i]) { // mismatch after j matches
            // Do not need to match lps[0..lps[j-1]] characters
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
}

ll exponentMod(int x, int y, ll n) {

    // base cases
    if (y == 0) return 1;
    if (x == 0) return 0;

    // y is even
    ll v;
    if (y % 2 == 0) {
        v = exponentMod(x, y / 2, n);
        v = (v * v) % n;
    }

    // y is odd
    else {
        v = x % n;
        v = (v * exponentMod(x, y - 1, n)) % n;
    }

    return (ll)((v + n) % n);
}


ll calcula_fatorial_mod(ll n){
    ll res = 1;
    for(int i = 2;i <= n; i++){
        res = res * i % MOD;
    }
    return res;

}

int main(){
    ll n; string pattern;
    cin >> n; cin >> pattern;
    ll permutations = calcula_fatorial_mod((n- pattern.size() +1));
    ll pot = exponentMod(26,n- pattern.size(),pow(10,9)+7);
    ll res = (permutations * pot) % MOD;
    cout << res << endl; 
}