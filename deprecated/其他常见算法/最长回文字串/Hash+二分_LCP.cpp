#include <iostream>
#include <stdio.h>
#include <string.h>
#define  maxn 200010
#define  tt   23
#define  pp   23
#define  ll   long long
using namespace std;
const ll mod = 10000007;
int T,N,length[maxn],ans,c[maxn];
ll H[maxn],TT[maxn];
bool judge(int x,int y,int mid){
     ll k1=H[x]-(H[x+mid]*TT[mid])%mod;
     ll k2=H[y]-(H[y+mid]*TT[mid])%mod;
     if(k1<0)k1+=mod;
     if(k2<0)k2+=mod;
     if(k1!=k2)return false;
     for(int l=0;l<mid;l++)
        if(c[x+l]!=c[y+l])return false;
     return true;
}
int getmin(int x,int y,int R){
    int l=0,r=R;
    while(l<r){
       int mid=l+r+1>>1;
       if(judge(x,y,mid))l=mid;
       else r=mid-1;
    }
    return l;
}
int main()
{
    cin>>T;
    TT[1]=tt;
    for(int i=2;i<=100000;i++)
       TT[i]=TT[i-1]*tt,TT[i]%=mod;
    while(T--){
       scanf("%d",&N);
       for(int i=0;i<N;i++)
          scanf("%d",&c[i]);
       if(N==1){cout<<1<<endl;continue;}
       length[N-1]=1;
       for(int i=N-2;i>=0;i--){
          if(c[i]>=c[i+1])length[i]=length[i+1]+1;
          else length[i]=1;
       }
       c[N]=1;
       for(int i=N;i<=2*N;i++)
          c[i]=c[2*N-i];
       N=2*N+1;
       H[N]=ans=0;
       for(int i=N-1;i>=0;i--)
          H[i]=H[i+1]*tt+c[i],H[i]%=mod;
       for(int i=0;i<N/2;i++){
          if(length[i]*2<=ans)continue;
          ans=max(ans,min(getmin(i,N-i-1,length[i]),length[i])*2-1);
          ans=max(ans,min(getmin(i,N-i,length[i]),length[i])*2);
       }
       printf("%d\n",ans);
    }
    //system("pause");
    return 0;
}
