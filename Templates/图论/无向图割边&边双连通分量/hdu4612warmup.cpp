//可以处理重边的变双连通分量。。
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>
#define  ll    long long
#define  maxn  200005
#define  inf   0x3fffffff
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;
int n,m,x,y,low[maxn],id,dfn[maxn],cnt=-1,first[maxn],f[maxn],ans;
int FIRST[maxn],CNT=-1;
struct edge{int next,v,u;bool cut,vis;}e[2000005],E[2000005];

void addedge(int u,int v){e[++cnt].next=first[u],first[u]=cnt,e[cnt].v=v,e[cnt].u=u,e[cnt].cut=e[cnt].vis=false;}
void ADDEDGE(int u,int v){E[++CNT].next=FIRST[u],FIRST[u]=CNT,E[CNT].v=v,E[CNT].u=u;}
int getf(int x){return f[x]==x?x:f[x]=getf(f[x]);}

void dfs(int x){
     low[x]=dfn[x]=++id;
     for(int i=first[x];i!=-1;i=e[i].next)if(!e[i].vis){
        int v=e[i].v;
        e[i].vis=e[i^1].vis=true;
        if(!dfn[v])dfs(v),low[x]=min(low[x],low[v]);
        else low[x]=min(low[x],dfn[v]);
     }
}
int temp,dist[maxn],pnt;
bool visit[maxn];

void bfs(int x){
     temp=0;
     for(int i=1;i<=n;i++)dist[i]=inf,visit[i]=false;
     queue<int>q;q.push(x);dist[x]=0;
     while(!q.empty()){
        int f=q.front();q.pop();
        visit[f]=true;
        for(int i=FIRST[f];i!=-1;i=E[i].next)if(!visit[E[i].v]){
           dist[E[i].v]=dist[f]+1;
           if(dist[E[i].v]>temp)temp=dist[E[i].v],pnt=E[i].v;
           q.push(E[i].v);
        }}
}
void init(){
    CNT=cnt=-1;
    ans=temp=id=pnt=0;
    for(int i=0;i<=n;i++){
    first[i]=FIRST[i]=-1,f[i]=i,dfn[i]=low[i]=0;}
}
int main(){
    while(scanf("%d%d",&n,&m)==2 && n && m){
        init();
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            addedge(x,y),addedge(y,x);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i])
                dfs(i);
        for(int i=0;i<=cnt;i++)
            if(low[e[i].v]>dfn[e[i].u])
                e[i].cut=e[i^1].cut=true,ans++;
        int kk;
        for(int i=0;i<=cnt;i++)
            if(e[i].cut==false){
                int fu=getf(e[i].u),fv=getf(e[i].v);
                f[fu]=fv;
            }
        for(int i=0;i<=cnt;i+=2){
            int fu=getf(e[i].u),fv=getf(e[i].v);
            if(fu!=fv)ADDEDGE(fu,fv),ADDEDGE(fv,fu);
            kk=fu;
        }
        //cout<<ans<<endl;
        bfs(kk);bfs(pnt);
        printf("%d\n",ans-temp);
    }
    return 0;
}
