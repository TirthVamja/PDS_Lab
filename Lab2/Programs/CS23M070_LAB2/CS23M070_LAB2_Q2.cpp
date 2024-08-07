#include <bits/stdc++.h>
using namespace std;
int main() {
    
    int l = 0, r = 0, n, sum = 0, len = INT_MAX, target;
    cin>>n>>target;
    vector<int> nums(n);
    for(int i=0;i<n;i++) cin>>nums[i];
    while (r < n) {
        sum += nums[r++];
        while (sum >= target) {
            len = min(len, r - l);
            sum -= nums[l++];
        }
    }
    int ans = (len == INT_MAX )? 0 : len;
    cout<<ans<<endl;
}