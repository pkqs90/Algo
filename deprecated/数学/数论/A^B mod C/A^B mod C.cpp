#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#pragma  comment(linker, "/STACK:36777216")
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-3
#define  maxn  50005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
using namespace std;
ll mod;
ll get_phi(ll x){
    ll res=x;
    for(int i=2;i*i<=x;i++)if(x%i==0){
        while(x%i==0)x/=i;
        res=res/i*(i-1);
    }
    if(x>1)res=res/x*(x-1);
    return res;
}
ll pow_mod(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1)res*=x,res%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return res;
}
ll a,c;
char ch[10000005];
int main(){
    while(scanf("%lld",&a)==1){
        scanf(" %s%lld",&ch,&c);
        mod=c;
        bool flag=false;
        ll phi=get_phi(c),b=0;
        for(int i=0,l=strlen(ch);i<l;i++){
            b=b*10+(ch[i]-'0');
            if(b>phi)b%=phi,flag=true;
        }
        if(flag)printf("%lld\n",pow_mod(a,b%phi+phi));
        else printf("%lld\n",pow_mod(a,b));
    }
}
