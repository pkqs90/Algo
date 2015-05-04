#include <iostream>
#include <stdio.h>
#include <cstring>
#define  maxn 50005
#define  ll long long
using namespace std;
int a,b,d,t,sump[maxn],ans;
int getp(int x){
     if(x==1)return 1;
     int tmp=-1,t=x;
     for(int i=2;i*i<=x;i++)if(x%i==0){
        x/=i;if(x%i==0)return 0;
        tmp*=-1;
     }
     return tmp;
}
int main(){
    scanf("%d",&t);
    for(int i=1;i<=maxn;i++)sump[i]=sump[i-1]+getp(i);
    while(t--){
       scanf("%d%d%d",&a,&b,&d);
       a=a/d,b=b/d,ans=0;
       for(int i=1;i<=min(a,b);i++){
          int m=min(a/(a/i),b/(b/i))-i;
          ans+=(sump[i+m]-sump[i-1])*(a/i)*(b/i);
          i+=m;
       }printf("%d\n",ans);
    }
    return 0;
}
