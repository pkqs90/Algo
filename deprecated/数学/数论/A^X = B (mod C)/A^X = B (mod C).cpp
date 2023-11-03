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
#define  maxn  200005
#define  maxm  10005
#define  ll    long long
#define  inf   0x7fffffff
#define  pb    push_back
#define  mod   100007
using namespace std;
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
struct edge{int next,v,id;}e[mod];
int first[mod],cnt;
void add_hash(int u,int num,int id){
    e[++cnt].next=first[u],first[u]=cnt,e[cnt].v=num,e[cnt].id=id;
}
int _hash(ll x){
    int res=inf;
    for(int i=first[x%mod];i!=-1;i=e[i].next)
        if(e[i].v==x)res=min(res,e[i].id);
    return res==inf?0:res;
}
void ext_gcd(ll a,ll b,ll &d,ll &x,ll &y){
     if(!b){d=a,x=1,y=0;}
     else{ext_gcd(b,a%b,d,y,x),y-=x*(a/b);}
}
ll inv(ll a,ll c){
    ll d,x,y;
    ext_gcd(a,c,d,x,y);
    return (x+c)%c;
}
ll pow_mod(ll x,ll y,ll mm){
    ll res=1;
    while(y){
       if(y&1)res*=x,res%=mm;
       x*=x,x%=mm,y>>=1;
    }
    return res%mm;
}
ll baby_step(ll a,ll b,ll c){//a^x = b (mod c)
    ll tt=1,tmp,co=0,d=1;
    memset(first,-1,sizeof(first)),cnt=-1;
    for(int i=0;i<=100;tt=tt*a%c,i++)if(tt==b)return i;
    while((tmp=gcd(a,c))!=1){
        if(b%tmp!=0)return -1;
        co++,b/=tmp,c/=tmp,d=d*a/tmp%c;
    }
    int m=(int)(sqrt(c+0.5));
    tt=1;
    for(int i=0;i<=m;i++)
        add_hash(tt%mod,tt,i),tt*=a,tt%=c;
    tt=pow_mod(a,m,c);
    for(int i=0;i<=m;i++){
        if(tmp=_hash(b*inv(d,c)%c))return i*m+tmp+co;
        d=d*tt%c;
    }
    return -1;
}
int main(){
    ll a,b,c;
    while(scanf("%lld%lld%lld",&a,&c,&b)==3){
        if(!a&&!c&&!b)break;
        b%=c;
        ll kk=baby_step(a,b,c);
        if(kk==-1)printf("No Solution\n");
        else printf("%d\n",baby_step(a,b,c));
    }
}
