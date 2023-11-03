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
#define  maxn  55555
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
using namespace std;
int tt,n,k,Q,m,son[maxn<<2];
struct pnt{int d[6];}a[maxn],tar,tree[maxn<<2];
bool operator <(const pnt &t1,const pnt &t2){return t1.d[tt]<t2.d[tt];}
priority_queue< pair<ll,pnt> >q;
ll sqr(ll x){return x*x;}
void init_tree(int l,int r,int dep,int x){
    if(l>r)return;
    int mid=(l+r)>>1;
    tt=dep%k;
    //按照tt=dep%k第tt维来排序
    son[x]=true;
    nth_element(a+l,a+mid,a+r+1);
    //第mid大的元素放在mid处,左边的比他小,右边的比他大
    tree[x]=a[mid];
    init_tree(l,mid-1,dep+1,lc(x));
    init_tree(mid+1,r,dep+1,rc(x));
}
void query(int dep,int x){
    if(!son[x])return;
    int lx=lc(x),rx=rc(x),flag=0,cur=dep%k;
    //这里的dep%k不能再用tt存了,不然会出错..why??
    pair<ll,pnt>res=make_pair(0,tree[x]);
    for(int i=0;i<k;i++)
        res.first+=sqr(tar.d[i]-tree[x].d[i]);
    if(tar.d[cur]>=tree[x].d[cur])swap(lx,rx);
    //把lx换为target所在的那一边
    query(dep+1,lx);
    //这里应该先递归左子树再判断这个点,可以减少大量时间..因为减少了递归右子树的可能性..
    if(q.size()<m)q.push(res);
    else if(q.top().first>res.first)q.pop(),q.push(res);
    //这里进行一下判断,是KD树优秀复杂度的保证
    if(sqr(tree[x].d[cur]-tar.d[cur])<q.top().first)flag=true;
    if(flag)query(dep+1,rx);
}
int main(){
    while(scanf("%d%d",&n,&k)==2){
        for(int i=1;i<=n;i++)
            for(int j=0;j<k;j++)
                scanf("%d",&a[i].d[j]);
        memset(son,0,sizeof(son));
        init_tree(1,n,0,1);
        scanf("%d",&Q);
        while(Q--){
            for(int i=0;i<k;i++)
                scanf("%d",&tar.d[i]);
            scanf("%d",&m);
            query(0,1);
            pnt ans[21];
            int cnt=0;
            while(!q.empty())ans[++cnt]=q.top().second,q.pop();
            printf("the closest %d points are:\n",m);
            for(int i=m;i>=1;i--)
                for(int j=0;j<k;j++)
                    printf("%d%s",ans[i].d[j],j==k-1?"\n":" ");
        }
    }
}
