#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, current_subarray_sum, min_len=INT_MAX, target;
    cin>>n>>target;
    vector<int> nums(n);
    for(int i=0;i<n;i++) cin>>nums[i];
    for (int i=0; i<n; i++) {
        current_subarray_sum = 0;
        for (int j=i; j<n; j++) {
            current_subarray_sum+=nums[j];
            if (current_subarray_sum >= target) min_len = min(min_len, j-i+1);
        }
    }
    int ans = min_len==INT_MAX?0:min_len;
    cout<<ans;
}