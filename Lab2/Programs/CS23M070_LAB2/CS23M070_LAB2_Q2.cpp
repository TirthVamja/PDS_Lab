#include <bits/stdc++.h>
using namespace std;
int main() {
    
    int l = 0, r = 0, n, sum = 0, len = INT_MAX, target;
    cin>>n>>target;
    vector<int> nums(n);
    // Input elements ...
    for(int i=0;i<n;i++) cin>>nums[i];

    // Using Two-Pointer Approach
    
    // Moving right pointer
    while (r < n) {
        sum += nums[r++];

        // Move left pointer until the sum of elements is >= target (we try to shrink subarray as much as possible)
        while (sum >= target) {
            // update minimum length
            len = min(len, r - l);
            sum -= nums[l++];
        }
    }
    // if sum of all elements < target, then ans=0
    int ans = (len == INT_MAX )? 0 : len;
    cout<<ans<<endl;
}