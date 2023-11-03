#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <math.h>
#define  maxn 1005
#define  maxm 2000005
#define  pb   push_back
#define  ll   long long
using namespace std;
bool f[maxn][maxn],flag[maxn];
int ans,n,m,a,b,dfn[maxn],low[maxn],index,scnt,stack[maxm][3],cnt,belong[maxn],col[maxn];
vector<int>e[maxn],ne[maxn];

void dfs(int x,int f){//求无向图的点双连通分量 
     low[x]=dfn[x]=++index;
     for(int i=0,s=e[x].size();i<s;i++)if(e[x][i]!=f){
        int v=e[x][i];
        if(!dfn[e[x][i]]){
           stack[++cnt][1]=x,stack[cnt][2]=v;
           dfs(e[x][i],x);
           low[x]=min(low[x],low[e[x][i]]);
           if(low[v]>=dfn[x]){
              ne[++scnt].clear();
              while(1){
                 int xx=stack[cnt][1],vv=stack[cnt--][2];
                 if(belong[xx]!=scnt)
                    ne[scnt].pb(xx),belong[xx]=scnt;
                 if(belong[vv]!=scnt)
                    ne[scnt].pb(vv),belong[vv]=scnt;
                 if(xx==x && vv==v)break;
              }
           }
        }
        else if(dfn[v]<dfn[x])
           low[x]=min(low[x],dfn[v]);
     }
}

bool dfs2(int x,int X){//进行染色 
     for(int i=0,s=e[x].size();i<s;i++)
        if(belong[e[x][i]]==X){
           if(col[e[x][i]]==col[x])return false;
           if(!col[e[x][i]]){
              col[e[x][i]]=3-col[x];
              if(!dfs2(e[x][i],X))return false;
           }
        }
     return true;
}              

void init(){
     index=scnt=cnt=0;
     ans=n;
     memset(f,0,sizeof(f));
     for(int i=1;i<=n;i++)
        e[i].clear(),ne[i].clear(),
        dfn[i]=low[i]=flag[i]=belong[i]=col[i]=0;
}

int main(){
    while(scanf("%d%d",&n,&m)&&n&&m){
       init();
       for(int i=1;i<=m;i++){
          scanf("%d%d",&a,&b);
             f[a][b]=f[b][a]=true;
       }
       for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)if(i!=j&&!f[i][j])
             e[i].pb(j);
       for(int i=1;i<=n;i++)
          if(!dfn[i])
             dfs(i,0);
       for(int i=1;i<=scnt;i++){
             memset(col,0,sizeof(col));//尼玛。。给劳资记得初始化啊= =/// 
             for(int j=0,s=ne[i].size();j<s;j++)
                belong[ne[i][j]]=i;
             col[ne[i][0]]=1;
             if(!dfs2(ne[i][0],i))
                for(int j=0,s=ne[i].size();j<s;j++)
                   flag[ne[i][j]]=true;
          }
       for(int i=1;i<=n;i++)
          ans-=flag[i];
       printf("%d\n",ans);
    }
    system("pause");
    return 0;
}
