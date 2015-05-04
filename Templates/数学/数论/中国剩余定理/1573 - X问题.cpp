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
#define  inf   1e9
#define  pb    push_back
#define  mod   1000000007
using namespace std;
ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
void ext_gcd(ll a,ll b,ll &d,ll &x,ll &y){
     if(!b){d=a,x=1,y=0;}
     else{ext_gcd(b,a%b,d,y,x),y-=x*(a/b);}
}
ll a[11],b[11];
int n,m,t;
ll China(int N,ll a[],ll b[]){
    ll d,x,y;
    a[0]=1,b[0]=1;
    for(int i=1;i<=N;i++){
        ext_gcd(a[i-1],a[i],d,x,y);
        if((b[i]-b[i-1])%d!=0)return -1;
        x*=(b[i]-b[i-1])/d;
        x%=(a[i]/d);if(x<0)x+=a[i]/d;
        int lcm=a[i]*a[i-1]/gcd(a[i],a[i-1]);
        a[i]=lcm;
        b[i]=(a[i-1]*x+b[i-1])%lcm;
    }
    return b[N];
}//N mod a[i] = b[i]
int main(){
    cin>>t;
    while(t--){
        scanf("%d%d",&n,&m);
        ll res=1,ans;
        memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
        for(int i=1;i<=m;i++)scanf("%I64d",&a[i]),res=res*a[i]/gcd(res,a[i]);
        for(int i=1;i<=m;i++)scanf("%I64d",&b[i]);
        for(int i=1;i<=10000;i++){
            bool flag=false;
            for(int j=1;j<=m;j++)
            if(i%a[j]!=b[j]){flag=true;break;}
            //if(!flag){cout<<i<<"!!"<<endl;break;}
        }
        ll now=China(m,a,b);
        if(now==-1){printf("0\n");continue;}
        //cout<<now<<endl;
        if(now<=n)ans=1,ans+=(n-now)/res-(now?0:1);else ans=0;
        printf("%d\n",ans);
    }
}
