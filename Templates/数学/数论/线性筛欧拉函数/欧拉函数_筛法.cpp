//poj 2478

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
#define  maxn  1000005
#define  maxm  50005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   0x7fffffffffffffffll
#define  pb    push_back
#define  mp    make_pair
using namespace std;
ll ans[maxn],phi[maxn],prime[maxn];
int n,cnt;
/*
void phi_table(){
     phi[1]=1;
     for(int i=2;i<maxn;i++)if(!phi[i])
        for(int j=i;j<maxn;j+=i){
           if(!phi[j])phi[j]=j;
           phi[j]=phi[j]/i*(i-1);
           //要先进行除法。。不然对于大质数直接溢出去了。。
        }
}*/

void phi_table(){
    phi[1]=1;
    for(int i=2;i<maxn;i++){
        if(!phi[i])phi[i]=i-1,prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++){
            if(i%prime[j]==0){phi[i*prime[j]]=phi[i]*prime[j];break;}
            else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}

void mu_table(){
    mu[1] = 1;
    for(int i = 0; i < N; i ++) is_prime[i] = true;
    for(int i = 2 ; i < N; i ++){
        if(is_prime[i]) prime.PB(i), mu[i] = -1;
        for(int j = 0; j < prime.size() && i * prime[j] < N; j ++){
            is_prime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for(int i = 1; i < N; i ++) if(mu[i] != 0)
        for(int j = i; j < N; j += i)
            vec[j].PB(i);
}

int main(){
    phi_table();
    /*for(int i=1;i<=10;i++)
        cout<<i<<' '<<phi[i]<<endl;*/
    ans[2]=1;
    for(int i=3;i<maxn;i++)
       ans[i]=ans[i-1]+phi[i];
    while(scanf("%d",&n)==1 && n){
       printf("%lld\n",ans[n]);
    }
    return 0;
}
