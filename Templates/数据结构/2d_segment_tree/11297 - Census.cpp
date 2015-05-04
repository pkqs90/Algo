#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  510
#define  maxm  2222
#define  ll    long long
#define  ull   unsigned long long
#define  inf   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  lowbit(x) (x&(-x))

using namespace std;

struct _2dseg{
    int lx,rx,ly,ry;
    int mn,mx;
    int midx(){return lx+rx>>1;}
    int midy(){return ly+ry>>1;}
}tree[maxn<<2][maxn<<2];

void build_treey(int x,int y,int lx,int rx,int ly,int ry){
    tree[x][y].lx=lx,tree[x][y].rx=rx;
    tree[x][y].ly=ly,tree[x][y].ry=ry;
    if(ly==ry)return;
    int midy=ly+ry>>1;
    if(ly<=midy)build_treey(x,lc(y),lx,rx,ly,midy);
    if(midy<ry)build_treey(x,rc(y),lx,rx,midy+1,ry);
}

void build_treex(int x,int y,int lx,int rx,int ly,int ry){
    tree[x][y].lx=lx,tree[x][y].rx=rx;
    tree[x][y].ly=ly,tree[x][y].ry=ry;
    build_treey(x,y,lx,rx,ly,ry);
    if(lx==rx)return;
    int midx=lx+rx>>1;
    if(lx<=midx)build_treex(lc(x),y,lx,midx,ly,ry);
    if(midx<rx)build_treex(rc(x),y,midx+1,rx,ly,ry);
}

int x_0,y_0,x_1,y_1,X,Y;

pair<int,int> calcy(int x,int y){

    if(y_0<=tree[x][y].ly && tree[x][y].ry<=y_1){
        return mp(tree[x][y].mn,tree[x][y].mx);
    }
    int midy=tree[x][y].midy();
    int mx=-inf,mn=inf;
    if(y_0<=midy){
        pair<int,int>tmp=calcy(x,lc(y));
        mn=min(mn,tmp.first);
        mx=max(mx,tmp.second);
    }
    if(midy<y_1){
        pair<int,int>tmp=calcy(x,rc(y));
        mn=min(mn,tmp.first);
        mx=max(mx,tmp.second);
    }
    //cout<<x<<' '<<y<<' '<<tree[x][y].lx<<' '<<tree[x][y].rx<<' '<<tree[x][y].ly<<' '<<tree[x][y].ry<<' '<<tree[x][y].mn<<' '<<tree[x][y].mx<<endl;
    return mp(mn,mx);
}

pair<int,int> calcx(int x,int y){
    if(x_0<=tree[x][y].lx && tree[x][y].rx<=x_1){
        return calcy(x,y);
    }
    int midx=tree[x][y].midx();
    int mx=-inf,mn=inf;
    if(x_0<=midx){
        pair<int,int>tmp=calcx(lc(x),y);
        mn=min(mn,tmp.first);
        mx=max(mx,tmp.second);
    }
    if(midx<x_1){
        pair<int,int>tmp=calcx(rc(x),y);
        mn=min(mn,tmp.first);
        mx=max(mx,tmp.second);
    }
    return mp(mn,mx);
}

void modifyy(int x,int y,int num,bool leaf){
    if(tree[x][y].ly==tree[x][y].ry){
        if(leaf)tree[x][y].mn=tree[x][y].mx=num;
        else{
            tree[x][y].mn=min(tree[lc(x)][y].mn,tree[rc(x)][y].mn);
            tree[x][y].mx=max(tree[lc(x)][y].mx,tree[rc(x)][y].mx);
        }
        return;
    }
    int midy=tree[x][y].midy();
    if(Y<=midy)modifyy(x,lc(y),num,leaf);
    else modifyy(x,rc(y),num,leaf);
    tree[x][y].mn=min(tree[x][lc(y)].mn,tree[x][rc(y)].mn);
    tree[x][y].mx=max(tree[x][lc(y)].mx,tree[x][rc(y)].mx);
}

void modifyx(int x,int y,int num){
    if(tree[x][y].lx==tree[x][y].rx){
        modifyy(x,y,num,true);
        return;
    }
    int midx=tree[x][y].midx();
    if(X<=midx)modifyx(lc(x),y,num);
    else modifyx(rc(x),y,num);
    modifyy(x,y,num,false);
}

int t,n,a,q,l,m;
char ch;

int main(){
    //freopen("read.in","r",stdin);
    while(scanf("%d%d",&n,&m)==2){
        memset(tree,0,sizeof(tree));
        build_treex(1,1,1,n,1,m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                scanf("%d",&a);
                X=i,Y=j;
                modifyx(1,1,a);
            }
        scanf("%d",&q);
        while(q--){
            scanf(" %c",&ch);
            if(ch=='c'){
                int num;
                scanf("%d%d%d",&X,&Y,&num);
                modifyx(1,1,num);
            }
            else{
                scanf("%d%d%d%d",&x_0,&y_0,&x_1,&y_1);
                pair<int,int>tmp=calcx(1,1);
                printf("%d %d\n",tmp.second,tmp.first);
            }
        }
    }
}
