//有依赖的背包问题 
#include <iostream>
#include <stdio.h>
#include <string.h>
#define  maxn 100005
#define  inf  0x7fffffff
using namespace std;
int dp1[maxn],dp2[maxn],N,V,W,n,w[11],c[11];
int main(){
    cin>>N>>V;
    for(int i=1;i<=N;i++){
       cin>>W>>n;
       for(int j=W;j<=V;j++)
          dp2[j]=dp1[j-W];
       for(int j=1;j<=n;j++){
          cin>>w[j]>>c[j];
          for(int k=V;k>=w[j]+W;k--)
             dp2[k]=max(dp2[k],dp2[k-w[j]]+c[j]);
       }
       for(int j=W;j<=V;j++)
          dp1[j]=max(dp1[j],dp2[j]);
    }
    cout<<dp1[V]<<endl;
    system("pause");
    return 0;
}
