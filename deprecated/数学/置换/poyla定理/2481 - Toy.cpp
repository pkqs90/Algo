#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <complex>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-3
#define  I     complex <double> (0,1)
#define  maxn  50005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  size  2
using namespace std;
struct Matrix{
       ll base[size][size];
       void init(){memset(base,0,sizeof(base));}
       void init2(){init();for(int i=0;i<size;i++)base[i][i]=1;}
       void debug(){
          for(int i=0;i<size;i++){
             for(int j=0;j<size;j++)
                cout<<base[i][j];
             cout<<endl;
          }cout<<endl;
       }
}start,trans,temp;
ll ans,mod,n;
ll Mul(ll x,ll y){
    ll res=0;
    x=(x%mod+mod)%mod,y=(y%mod+mod)%mod;
    while(y){
        if(y&1)res+=x,res%=mod;
        y>>=1,x<<=1,x%=mod;
    }
    return res%mod;
}
void copy(Matrix &a,Matrix b){
     for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
           a.base[i][j]=b.base[i][j];
}
void go(Matrix &a,Matrix b){
     Matrix temp;
     temp.init();
     for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
           for(int k=0;k<size;k++)
              temp.base[i][j]+=Mul(a.base[i][k],b.base[k][j]),temp.base[i][j]%=mod;
     copy(a,temp);
}
void multiply(int x){
     while(x){
        if(x&1)go(start,trans);
        go(trans,trans);
        x>>=1;
     }
}
ll get_phi(int x){
    ll res=x;
    for(int i=2;i*i<=x;i++)if(x%i==0){
        while(x%i==0)x/=i;
        res=res/i*(i-1);
    }
    if(x>1)res=res/x*(x-1);
    return res;
}
ll get_ans(int x){
    if(x==1)return 1;
    if(x==2)return 5;
    trans.init();trans.base[0][0]=3,trans.base[0][1]=-1,trans.base[1][0]=1;
    start.init2();
    multiply(x-2);
    ll k1=3*start.base[0][0]+start.base[0][1];
    ll k2=3*start.base[1][0]+start.base[1][1];
    //Zk1=(k1%mod+mod)%mod;
    ll ret=(((k1+2*(k1-k2-1))%mod)+mod)%mod;;
    return ret;
}
int main(){
    while(scanf("%I64d%I64d",&n,&mod)==2){
        ans=0,mod*=n;
        for(int i=1;i*i<=n;i++)if(n%i==0){
            if(i*i!=n)ans+=Mul(get_phi(n/i),get_ans(i))+Mul(get_phi(i),get_ans(n/i)),ans%=mod;
            else ans+=Mul(get_phi(i),get_ans(i)),ans%=mod;
        }
        printf("%I64d\n",(ans/n)%(mod/n));
    }
}
