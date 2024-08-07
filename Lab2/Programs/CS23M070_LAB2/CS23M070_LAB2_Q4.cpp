#include <bits/stdc++.h>
#define int  long long
using namespace std;
signed main() {
    int n,x,y; cin>>n>>x>>y;
    int l=0,r=2000000001;
    while(r-l>1){
        int m=(l+r)/2;
        int t=(m/min(x,y))+((m-min(x,y))/max(x,y));
        if(t>=n) r=m;
        else l=m;
    }
    cout<<r<<endl;
}