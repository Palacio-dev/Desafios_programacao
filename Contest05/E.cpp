#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    double p;
    cin >> n >> p;
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0.0));
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = 1.0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = p * dp[i - 1][j] + (1.0 - p) * dp[i][j - 1];
        }
    }
    double result = dp[n][n];
    cout << fixed << setprecision(2) << result << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}