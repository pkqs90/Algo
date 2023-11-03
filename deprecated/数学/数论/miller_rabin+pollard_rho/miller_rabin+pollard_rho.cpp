//poj 1811
#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
#include <time.h>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-11
#define  maxn  200005
#define  maxm  50005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   0x7fffffffffffffffll
#define  pb    push_back
#define  mp    make_pair
using namespace std;
ll ans;
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
ll mul_mod(ll x,ll y,ll k){
    x%=k,y%=k;
    ll res=0;
    while(y){
        if(y&1){
            res+=x;
            if(res>=k)res-=k;
        }
        x+=x,y>>=1;
        if(x>=k)x-=k;
    }
    return res;
}
ll pow_mod(ll x,ll y,ll k){
    ll res=1;
    while(y){
        if(y&1)res=mul_mod(res,x,k);
        x=mul_mod(x,x,k),y>>=1;
    }
    return res;
}
ll witness(ll a,ll b,ll c){
    if(b==0)return 1;
    ll x,y,t=0;
    while((b&1)==0)
        b>>=1,t++;
    y=x=pow_mod(a,b,c);
    while(t--){
        y=mul_mod(x,x,c);
        if(y==1 && x!=1 && x!=c-1)
            return false;
        x=y;
    }
    return y==1;
}
bool miller_rabin(ll n) {//..质数为true, 非质数为false..
    if(n==2)return true;
    if(n<2 || (n&1)==0)return false;
    for(int i=0;i<3;i++)
        if(witness(rand()%(n-2)+2,n-1,n)!=1)
            return false;
    return true;
}
ll pollard_rho(ll n,ll c){//..随机返回一个 n 的约数..
    if(n%2==0)return 2;
    ll i=1,k=2,x=rand()%n,y=x,d;
    while(1){
        i++;
        x=(mul_mod(x,x,n)+c)%n;
        d=gcd(y-x,n);
        if(d==n)return n;
        if(d!=n && d>1)return d;
        if(i==k) y=x,k<<=1;
    }
}
void calc(ll n,ll c=240){//寻找最小的约数..
    if(n==1)return;
    if(miller_rabin(n)){
        ans=min(ans,n);
        return;
    }
    ll k=n;
    while(k==n)k=pollard_rho(n,c--);
    calc(k,c),calc(n/k,c);
}
ll n;
int t;
int main(){
    cin>>t;
    while(t--){
        scanf("%lld",&n);
        if(miller_rabin(n))printf("Prime\n");
        else{
            ans=inf;
            calc(n);
            printf("%lld\n",ans);
        }
    }
}
