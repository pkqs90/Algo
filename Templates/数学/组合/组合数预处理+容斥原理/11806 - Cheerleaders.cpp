#include <iostream>
#include <stdio.h>
#define  maxn 22
#define  maxm 100005
#define  maxs 1<<21
#define  mod  1000007
using namespace std;
int cnt,t,n,m,k,C[510][510];
int main(){
    cin>>t;
    for(int i=0;i<=505;i++)
       for(int j=0;j<=i;j++)
          C[i][j]=j?(C[i-1][j]+C[i-1][j-1])%mod:1;
    cout<<C[50][25]<<endl;
    while(t--){
       cin>>n>>m>>k;
       int ans=0;
       for(int s=0;s<16;s++){
          int b=0,r=n,c=m;
          if(s&1)r--,b++;
          if(s&2)r--,b++;
          if(s&4)c--,b++;
          if(s&8)c--,b++;
          if(b&1)ans=(ans+mod-C[r*c][k])%mod;
          else ans=(ans+C[r*c][k])%mod;
       }
       printf("Case %d: %d\n",++cnt,ans);
    }
//    system("pause");
    return 0;
}
