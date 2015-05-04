//Poj 3468
#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  100011
#define  maxm  10005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   1e9
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
using namespace std;
ll sum_1[maxn],sum_2[maxn],a[maxn],v,n,q,l,r;
char ch;
void insert(ll sum[],int x,ll v){
    for(;x<=n;x+=lowbit(x))
        sum[x]+=v;
}
ll query(ll sum[],int x){
    ll res=0;
    for(;x;x-=lowbit(x))
        res+=sum[x];
    return res;
}
ll get_sum(int x){
    return (ll)(x+1)*query(sum_1,x)-query(sum_2,x);
}
int main(){
    while(scanf("%d%d",&n,&q)==2){
        memset(sum_1,0,sizeof(sum_1));
        memset(sum_2,0,sizeof(sum_2));
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        for(int i=n;i>=2;i--){
            a[i]=a[i]-a[i-1];
            insert(sum_1,i,a[i]);
            insert(sum_2,i,i*a[i]);
        }
        insert(sum_1,1,a[1]);
        insert(sum_2,1,1*a[1]);
        while(q--){
            scanf(" %c",&ch);
            if(ch=='Q'){
                scanf("%d%d",&l,&r);
                printf("%lld\n",get_sum(r)-get_sum(l-1));
            }
            else{
                scanf("%lld%lld%lld",&l,&r,&v);
                insert(sum_1,l,v),insert(sum_1,r+1,-v);
                insert(sum_2,l,l*v),insert(sum_2,r+1,-(r+1)*v);
            }
        }
    }
}
