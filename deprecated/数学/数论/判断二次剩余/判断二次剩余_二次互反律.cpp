//UVA 10831
#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  100005
#define  maxm  10005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   1e9
#define  pb    push_back
#define  mp    make_pair
#define  lowbit(x) (x&(-x))
using namespace std;

ll pow_mod(ll x,ll y,ll mod){
    ll ret=1;
    while(y){
        if(y&1)ret*=x,ret%=mod;
        x*=x,x%=mod,y>>=1;
    }
    return ret;
}

// x*x == a (mod n) n should be a prime and gcd(a,n) == 1
// by discover
ll sqrt_mod(ll a,ll n){
    ll ret;
    if(!a || n==2 || n==1)return a%n;
    if(pow_mod(a,(n-1)/2,n)==1){
        if(n%4==3)ret=pow_mod(a,(n+1)/4,n);
        else{
            ll b=1,k=0,i=(n-1)/2;
            while(pow_mod(b,(n-1)/2,n)==1)b++;
            do{
                i/=2,k/=2;
                if((pow_mod(a,i,n)*(ll)pow_mod(b,k,n)+1==0)%n)
                    k+=(n-1)/2;
            }while(i%2==0);
            ret=(pow_mod(a,(i+1)/2,n)*(ll)pow_mod(b,k/2,n))%n;
        }
        return min(ret,n-ret);// make that res <= n/2
    }
    else return -1;
}

ll n,m;

int main(){
    while(scanf("%lld%lld",&n,&m)==2){
        if(n==-1 && m==-1)break;
        n%=m;
        printf("%s\n",sqrt_mod(n,m)==-1?"No":"Yes");
    }
}
