//Tyvj 1716
#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  2050
#define  maxm  10005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   1e9
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
using namespace std;
int sum[4][maxn][maxn],v,n,m,l0,r0,l1,r1,c;
char ch;
void insert(int s[][maxn],int x,int y,int v){
    for(;x<=n;x+=lowbit(x))
        for(int t=y;t<=m;t+=lowbit(t))
            s[x][t]+=v;
}
int query(int s[][maxn],int x,int y){
    ll res=0;
    for(;x;x-=lowbit(x))
        for(int t=y;t;t-=lowbit(t))
            res+=s[x][t];
    return res;
}
int get_sum(int x,int y){
    ll res0=query(sum[0],x,y)*(x+1)*(y+1);
    ll res1=query(sum[1],x,y)*(x+1);
    ll res2=query(sum[2],x,y)*(y+1);
    ll res3=query(sum[3],x,y);
    //cout<<res0<<' '<<res1<<' '<<res2<<' '<<res3<<endl;
    return res0-res1-res2+res3;
}
int main(){
    scanf("%c%d%d",&ch,&n,&m);
    while(scanf(" %c",&ch)==1){
        if(ch=='L'){
            scanf("%d%d%d%d%d",&l0,&r0,&l1,&r1,&c);
            insert(sum[0],l0,r0,c);insert(sum[0],l1+1,r0,-c);insert(sum[0],l0,r1+1,-c);insert(sum[0],l1+1,r1+1,c);
            insert(sum[1],l0,r0,c*r0);insert(sum[1],l1+1,r0,-c*r0);insert(sum[1],l0,r1+1,-c*(r1+1));insert(sum[1],l1+1,r1+1,c*(r1+1));
            insert(sum[2],l0,r0,c*l0);insert(sum[2],l1+1,r0,-c*(l1+1));insert(sum[2],l0,r1+1,-c*l0);insert(sum[2],l1+1,r1+1,c*(l1+1));
            insert(sum[3],l0,r0,c*l0*r0);insert(sum[3],l1+1,r0,-c*(l1+1)*r0);insert(sum[3],l0,r1+1,-c*l0*(r1+1));insert(sum[3],l1+1,r1+1,c*(l1+1)*(r1+1));
        }
        if(ch=='k'){
            scanf("%d%d%d%d",&l0,&r0,&l1,&r1);
            //cout<<get_sum(l1,r1)<<' '<<get_sum(l0-1,r1)<<' '<<get_sum(l1,r0-1)<<' '<<get_sum(l0-1,r0-1)<<endl;
            printf("%d\n",get_sum(l1,r1)-get_sum(l0-1,r1)-get_sum(l1,r0-1)+get_sum(l0-1,r0-1));
        }
    }
}
