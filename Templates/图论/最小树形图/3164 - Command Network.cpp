//poj3164

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#include <math.h>
#define  maxn 205
#define  maxm 20005
#define  inf  0x7fffffff
#define  ll   long long
#define  pb   push_back
using namespace std;
struct pnt {double x,y;}a[maxn];
struct edge{int u,v,next;double c;}e[maxm];
int n,m,x,y,pre[maxn],cnt=-1,id[maxn],first[maxn],index,visit[maxn];
double mincost[maxn],ans;
bool flag[maxn];

double get_dist(int p,int q){
       return sqrt((a[p].x-a[q].x)*(a[p].x-a[q].x)+(a[p].y-a[q].y)*(a[p].y-a[q].y));
}

void addedge(int u,int v,double c){
     e[++cnt].next=first[u],first[u]=cnt,e[cnt].v=v,e[cnt].u=u,e[cnt].c=c;
}

int dfs(int x){
    flag[x]=true;
    int num=1;
    for(int i=first[x];i!=-1;i=e[i].next)if(!flag[e[i].v])
       num+=dfs(e[i].v);
    return num;
}

void directed_mst(int root){
     int size=n;
     while(1){
        for(int i=1;i<=size;i++)
           mincost[i]=inf;
        for(int i=0;i<=cnt;i++)
           if(mincost[e[i].v]>e[i].c && e[i].u!=e[i].v){
              mincost[e[i].v]=e[i].c;
              pre[e[i].v]=e[i].u;
           }
        mincost[root]=0;
        memset(id,0,sizeof(id));
        memset(visit,0,sizeof(visit));
        int index=0;
        for(int i=1;i<=size;i++){
           ans+=mincost[i];
           int v=i;
           while(v!=root && visit[v]!=i && !id[v])
              visit[v]=i,v=pre[v];
           if(v!=root && !id[v]){
              id[v]=++index;
              for(int u=pre[v];u!=v;u=pre[u])
                 id[u]=index;
           }
        }
        if(!index)break;
        for(int i=1;i<=size;i++)
           if(!id[i])id[i]=++index;
        for(int i=0;i<=cnt;i++){
           int v=e[i].v;
           e[i].u=id[e[i].u];
           e[i].v=id[e[i].v];
           if(e[i].u!=e[i].v)
              e[i].c-=mincost[v];
        }
        size=index;
        root=id[root];
     }
     printf("%.2lf\n",ans);
}

void init(){
     cnt=-1,ans=0;
     for(int i=1;i<=n;i++)
        first[i]=-1,flag[i]=false;
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
       init();
       for(int i=1;i<=n;i++)
          scanf("%lf%lf",&a[i].x,&a[i].y);
       for(int i=1;i<=m;i++){
          scanf("%d%d",&x,&y);
          if(x!=y)
             addedge(x,y,get_dist(x,y));
       }
       if(dfs(1)!=n)printf("poor snoopy\n");
       else directed_mst(1);
    }
    return 0;
}
