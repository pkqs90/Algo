#include <iostream>
#include <stdio.h>
#include <string.h>
#define  ll  long long
#define  mod 1000000007
using namespace std;
ll n,m,f[20][2][7][7],f2[20][2][7][7],f3[20][2][7][7],ten[20],dig[20];
int t;
ll mul(ll a,ll b){return (a*b)%mod;}
ll dp(int pos,bool _7,int dsum,int sum,bool flag){
   if(pos==-1)return (!_7)&&(dsum!=0)&&(sum!=0);
   if(_7)return 0;
   if(!flag&&f[pos][_7][dsum][sum]!=-1)return f[pos][_7][dsum][sum];
   ll res=0;
   for(int i=0,l=flag?dig[pos]:9;i<=l;i++)
      res=(res+dp(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l))%mod;
   return flag?res:f[pos][_7][dsum][sum]=res;
}
ll dp2(int pos,bool _7,int dsum,int sum,bool flag){
   if(pos==-1)return 0;
   if(!flag&&f2[pos][_7][dsum][sum]!=-1)return f2[pos][_7][dsum][sum];
   ll res=0;
   for(int i=0,l=flag?dig[pos]:9;i<=l;i++){
      ll has=dp(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l);
      ll tmp=mul(i,ten[pos]);
      tmp=mul(tmp,has);
      res=(res+dp2(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l))%mod;
      res=(res+tmp)%mod;
   }
   return flag?res:f2[pos][_7][dsum][sum]=res;
}
ll dp3(int pos,bool _7,int dsum,int sum,bool flag){
   if(pos==-1)return 0;
   if(!flag&&f3[pos][_7][dsum][sum]!=-1)return f3[pos][_7][dsum][sum];
   ll res=0;
   for(int i=0,l=flag?dig[pos]:9;i<=l;i++){
      ll k1=dp(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l);
      ll k2=dp2(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l);
      ll tmp=mul(i,ten[pos]);
      res=(res+dp3(pos-1,_7|i==7,(dsum+i)%7,(sum*10+i)%7,flag&&i==l))%mod;
      res=(res+mul(2,mul(tmp,k2)))%mod;
      res=(res+mul(k1,mul(tmp,tmp)))%mod;
   }
   return flag?res:f3[pos][_7][dsum][sum]=res;
}
ll go(ll x){int cnt=0;
   while(x)dig[cnt++]=x%10,x/=10;
   return dp3(cnt-1,0,0,0,1)%mod;
}
int main(){
    scanf("%d",&t);
    memset(f,-1,sizeof(f));
    memset(f2,-1,sizeof(f2));
    memset(f3,-1,sizeof(f3));
    ten[0]=1;
    for(int i=1;i<20;i++)ten[i]=(ten[i-1]*10)%mod;
    while(t--){
       scanf("%I64d%I64d",&n,&m);
       printf("%I64d\n",((go(m)-go(n-1))%mod+mod)%mod);
    }
    system("pause");
    return 0;
}
