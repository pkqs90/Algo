#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  10010
#define  maxm  2222
#define  ll    long long
#define  ull   unsigned long long
#define  inf   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
using namespace std;

ll mod;

ll calc_det(ll a[][201],int n){
    //..n^3lgn..
    ll ret=1;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++)
            while(a[j][i]){
                ll t=a[i][i]/a[j][i];
                for(int k=i;k<n;k++)
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                for(int k=i;k<n;k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)return 0;
        ret=ret*a[i][i],ret%=mod;
    }
    ret=((ret%mod)+mod)%mod;
    return ret;
}

int x,y,n;
ll a[201][201];

int main(){
    while(scanf("%d%lld",&n,&mod)==2){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%lld",&a[i][j]);
        printf("%lld\n",calc_det(a,n));
    }
}
