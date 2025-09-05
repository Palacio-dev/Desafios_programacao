#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> get_sums(const vector<ll>& nums) {
    int n = nums.size();
    vector<ll> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) s += nums[i];
        }
        sums.push_back(s);
    }
    return sums;
}

int main(){
    ll n, x;
    cin >> n >> x;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    vector<ll> A(nums.begin(), nums.begin() + n / 2);
    vector<ll> B(nums.begin() + n / 2, nums.end());
    vector<ll> sumsA = get_sums(A);
    vector<ll> sumsB = get_sums(B);
    sort(sumsB.begin(), sumsB.end());  
    ll ans = 0;
    for (auto s : sumsA) {
        ll need = x - s;
        auto range = equal_range(sumsB.begin(), sumsB.end(), need);
        ans += (range.second - range.first); 
    }
    cout << ans << endl;
}