#include <bits/stdc++.h>
#define int  long long
using namespace std;
signed main() {
    int n,x,y; cin>>n>>x>>y;
    // Setting limits of Binary Search on Time
    int l=0,r=2000000001;
    while(r-l>1){
        int m=(l+r)/2;

        // Find number of copies we can get in m seconds
        int t=(m/min(x,y))+((m-min(x,y))/max(x,y));
        
        // check whether we can create atleast n copies in m seconds.
        if(t>=n) r=m;
        else l=m;
    }
    cout<<r<<endl;
}