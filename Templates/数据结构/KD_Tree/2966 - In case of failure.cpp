#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-3
#define  maxn  100005
#define  maxm  10005
#define  ll    long long
#define  inf   0x7fffffffffffffffll
#define  pb    push_back
using namespace std;
int tt,n,k=2,t,son[maxn<<2];
ll ans;
struct pnt{ll d[2];int id;}a[maxn],tar,tree[maxn<<2];
bool operator <(const pnt &t1,const pnt &t2){return t1.d[tt]<t2.d[tt];}
ll sqr(ll x){return x*x;}
void init_tree(int l,int r,int dep,int x){
    if(l>r)return;
    int mid=l+r>>1;
    tt=dep%k;
    son[x]=true;
    nth_element(a+l,a+mid,a+r+1);
    tree[x]=a[mid];
    init_tree(l,mid-1,dep+1,lc(x));
    init_tree(mid+1,r,dep+1,rc(x));
}
void query(int dep,int x){
    if(!son[x])return;
    int lx=lc(x),rx=rc(x),cur=dep%k;
    ll res=0,tmp=inf;
    if(tar.d[cur]>=tree[x].d[cur])swap(lx,rx);
    for(int i=0;i<k;i++)
        res+=sqr(tar.d[i]-tree[x].d[i]);
    if(res==0)res=inf;
    ans=min(ans,res);
    query(dep+1,lx);
    if(sqr(tree[x].d[cur]-tar.d[cur])<ans)query(dep+1,rx);
}

bool cmp(const pnt &k1,const pnt &k2){return k1.id<k2.id;}
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        memset(son,0,sizeof(son));
        for(int i=1;i<=n;i++)
            scanf("%I64d%I64d",&a[i].d[0],&a[i].d[1]),a[i].id=i;
        init_tree(1,n,0,1);
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++){
            ans=inf,tar=a[i];
            query(0,1);
            printf("%I64d\n",ans);
        }
    }
}

