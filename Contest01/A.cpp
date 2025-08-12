#include <iostream>
using namespace std;

bool verify_divisibility(long long  a, long long b) {
    if (b == 0) {
        return false; // Avoid division by zero
    }
    return a % b == 0;
}

int main() {
    int cont = 0;
    long long  n, k, temp;
    cin >> n >> k;
    long long v[k];
    for (int i = 0; i < k; i++) {
        cin >> v[i]; 
    }

    for (int i = 2; i <= n; i++){
        for (int j : v) {
            if (verify_divisibility(i, j)) {
                cont++;
                break; // Stop checking once we find a valid divisor
            }
        }
    }
    cout << cont << endl; // Output the count of valid indices
}
    