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
#define  mod   999911659
using namespace std;
ll fac[4]={2,3,4679,35617};
ll n,g,res;
ll pow_mod(ll x,ll y){
    ll res=1;
    while(y){
       if(y&1)res*=x,res%=mod;
       x*=x,x%=mod,y>>=1;
    }
    return res%mod;
}//快速幂
void ext_gcd(ll a,ll b,ll &d,ll &x,ll &y){
     if(!b){d=a,x=1,y=0;}
     else{ext_gcd(b,a%b,d,y,x),y-=x*(a/b);}
}//扩展欧几里得
ll inv(ll a,ll c){
    ll d,x,y;
    ext_gcd(a,c,d,x,y);
    return (x+c)%c;
}//逆元
ll calc(ll x,ll y,ll c){
    if(x<y)return 0;
    ll res1=1,res2=1;
    for(int i=1;i<=y;i++)
        res1*=(x-i+1),res1%=c,res2*=i,res2%=c;
    res2=inv(res2,c),res1*=res2,res1%=c;
    return res1;
}//C(x,y)%c,直接算
ll lucas(ll x,ll y,ll c){
    ll res=1;
    while(x&&y&&res)res*=calc(x%c,y%c,c),res%=c,x/=c,y/=c;
    return res;
}//C(x,y)%c,Lucas定理
ll equ(ll a,ll b,ll c){
    // ax + cy = b
    ll d,x,y;ext_gcd(a,c,d,x,y);
    if(b%d!=0)return -1;
    x*=(b/d),x%=(c/d);if(x<0)x+=(c/d);
    return x;
}//求解模方程ax = b mod c, 最小满足要求的正整数x
ll China(int N,ll a[],ll m[]){
    ll M=1,res=0;
    for(int i=0;i<N;i++)M*=m[i];
    //cout<<M<<endl;
    for(int i=0;i<N;i++){
        ll w=M/m[i];
        res+=w*equ(w,a[i],m[i]),res%=(mod-1);
    }
    return res;
}//中国剩余定理 x mod m[i] = a[i]..要求m[i]之间互质
ll go(ll x){
    // a^b % c = a^(b%phi(c)+phi(c)) % c (b>phi(c))
    // 这里不用判断b>phi(c)是因为c是质数,因此一定有a^phi(c) = 1 (mod c)..因此也就无所谓了
    // phi(c)不为质数,分解质因数后用中国剩余定理合并
    ll a[4];
    for(int i=0;i<4;i++)a[i]=lucas(n,x,fac[i]);
    /*for(int i=0;i<4;i++)cout<<a[i]<<endl;
    cout<<endl;*/
    ll res=China(4,a,fac);
    return res;//+mod-1;
}
int main(){
    scanf("%lld%lld",&n,&g);
    for(int i=1;i*i<=n;i++)if(n%i==0){
        if(i*i!=n)res+=go(i),res+=go(n/i);
        if(i*i==n)res+=go(i);
    }
    printf("%lld\n",pow_mod(g,res));
}
