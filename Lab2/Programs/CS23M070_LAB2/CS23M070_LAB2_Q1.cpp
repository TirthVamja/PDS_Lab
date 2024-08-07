#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, current_subarray_sum, min_len=INT_MAX, target;
    cin>>n>>target;
    vector<int> nums(n);
    // Input elements
    for(int i=0;i<n;i++) cin>>nums[i];

    // Naive Approach, for every subarray calculate its sum and compare with target
    for (int i=0; i<n; i++) {
        current_subarray_sum = 0;
        for (int j=i; j<n; j++) {
            // calculate subarray sum
            current_subarray_sum+=nums[j];
            // compare sum with target, and update minimum length if required.
            if (current_subarray_sum >= target) min_len = min(min_len, j-i+1);
        }
    }
    // if sum of all elements < target, then ans=0
    int ans = min_len==INT_MAX?0:min_len;
    cout<<ans;
}