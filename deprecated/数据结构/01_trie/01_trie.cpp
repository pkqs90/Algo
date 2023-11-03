#include <iostream>
#include <stdio.h>
#define  maxn 100005
#define  ll   long long
#define  inf  0x7fffffff
using namespace std;
struct tree{int son[2];}tree[maxn*51];
int n,size;
ll a[maxn],s,t,ans;
ll max(ll a,ll b){return a>b?a:b;}
void insert(ll x){
     int p=0;//注意建树的顺序..显然应该从高位往低位建..
     for(int i=50;i>=0;i--){
        bool temp=x&(1LL<<i);
        if(!tree[p].son[temp])
           tree[p].son[temp]=++size;
        p=tree[p].son[temp];
     }
}
ll check(ll x){
   ll ans=0;
   int p=0;
   for(int i=50;i>=0;i--){
      bool temp=!(x&((1LL)<<i));
      if(tree[p].son[temp])
         p=tree[p].son[temp],ans|=(1LL<<i);
      else
         p=tree[p].son[!temp];
   }
   return ans;
}
int main(){
    cin>>n;
    insert(0);
    for(int i=1;i<=n;i++){
       scanf("%I64d",&a[i]);
       s^=a[i],insert(s);
    }
    ans=check(0);
    for(int i=n;i>=1;i--){
       t^=a[i];
       ans=max(ans,check(t));
    }
    printf("%I64d\n",ans);
    return 0;
}
