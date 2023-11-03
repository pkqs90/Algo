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
#define  maxn  50005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  mod   2007
using namespace std;
struct query{int l,r,id;ll ans1,ans2;}q[maxn];
ll num[maxn];
int n,m,a[maxn];

ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}

bool cmp1(const query &a,const query &b){
    int k1=a.l/sqrt(n),k2=b.l/sqrt(n);
    if(k1!=k2)return k1<k2;
    return a.r<b.r;
}

bool cmp2(const query &a,const query &b){return a.id<b.id;}

int main(){
    while(scanf("%d%d",&n,&m)==2){
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=m;i++)
            scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
        sort(q+1,q+1+m,cmp1);
        int head=1,tail=1;num[a[1]]++;
        ll res=0;
        for(int i=1;i<=m;i++){
            while(head<q[i].l)res-=--num[a[head]],head++;
            while(head>q[i].l)head--,res+=num[a[head]]++;
            while(tail<q[i].r)tail++,res+=num[a[tail]]++;
            while(tail>q[i].r)res-=--num[a[tail]],tail--;
            q[i].ans1=res,q[i].ans2=(ll)(q[i].r-q[i].l+1)*(ll)(q[i].r-q[i].l)/2;
            //cout<<q[i].l<<' '<<q[i].r<<' '<<res<<endl;
        }
        sort(q+1,q+1+m,cmp2);
        for(int i=1;i<=m;i++){
            ll tmp=gcd(q[i].ans1,q[i].ans2);
            if(q[i].ans1==0)printf("0/1\n");
            else printf("%lld/%lld\n",q[i].ans1/tmp,q[i].ans2/tmp);
        }
    }
}
