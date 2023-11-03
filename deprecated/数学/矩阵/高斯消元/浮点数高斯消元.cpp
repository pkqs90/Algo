//Hdu 2262 - Bad Wiring
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
#define  eps   1e-8
#define  maxn  505
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  mod   2007
using namespace std;
bool flag[maxn],FLAG;
int way[5],d[maxn],S,n,m;
double mat[maxn][maxn],ans[maxn];
char ch[25][25];
void bfs(int x){
    queue<int>q;
    memset(flag,0,sizeof(flag));
    q.push(x),flag[x]=true;
    while(!q.empty()){
        int f=q.front();q.pop();
        if(ch[f/m][f%m]=='$')continue;
        for(int i=0;i<4;i++){
            if(f%m==m-1&&i==0)continue;
            if(f%m==0&&i==1)continue;
            if(f/m==n-1&&i==2)continue;
            if(f/m==0&&i==3)continue;
            int k=f+way[i];
            if(ch[k/m][k%m]=='#')continue;
            d[f]++;
            if(!flag[k])q.push(k),flag[k]=true;
        }
    }
}
void init(){
    way[0]=1,way[1]=-1,way[2]=m,way[3]=-m;
    memset(d,0,sizeof(d));
    memset(a,0,sizeof(a)),memset(ans,0,sizeof(ans));
    FLAG=false;
}
void Gauss(int n, int m){
    int i, j, k;
    for(i = 0, j = 0; i < n && j < m; j ++){
        k = i;
        for(int r = i + 1; r < n; r ++)
            if(fabs(mat[k][j]) < fabs(mat[r][j]))
                k = r;
        //找到一个大一点的精度好控制一些..但是这种写法是基于一定有解的
        if(k < n){
            if(i != k) for(int t = 0; t <= m; t ++) swap(mat[i][t], mat[k][t]);
            //如果这里是从0开始枚举的话很容易就精度溢出了..因为每次都得消一遍..
            for(int r = i + 1; r < n; r ++)
                if(fabs(mat[r][j]) > EPS){//这里一定要用eps来判断..
                    double tt = mat[i][j] / mat[r][j];
                    //注意这里tt的顺序如果是mat[r][j]/mat[i][j]的话就很可能精度不够..不过是为啥..?..
                    for(int t = m; t >= 0; t --)
                        mat[r][t] -= mat[i][t] / tt;
                }
            i ++;
        }
    }
    for(int r = m - 1; r >= 0; r --){
        if(mat[r][r] == 0.0) continue;//有必要..因为某些点本身不会被涉及到..
        double tmp = 0.0;
        for(int t = r + 1; t < m; t ++)
            tmp += mat[r][t] * ans[t];
        ans[r] = (mat[r][m] - tmp) / mat[r][r];
    }
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        for(int i=0;i<n;i++)
            scanf(" %s",&ch[i]);
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(ch[i][j]=='@')
                    S=i*m+j,bfs(i*m+j);
        //f[i] = Σf[adj]/d[i] + 1 -> -Σf[adj] + d[i] * f[i] = d[i]
        for(int i=0;i<n*m;i++)if(flag[i]){
            if(ch[i/m][i%m]=='$'){mat[i][i]=1,mat[i][n*m]=0;FLAG=true;continue;}
            mat[i][i]=d[i],mat[i][n*m]=d[i];
            for(int j=0;j<4;j++){
                if(i%m==m-1&&j==0)continue;
                if(i%m==0&&j==1)continue;
                if(i/m==n-1&&j==2)continue;
                if(i/m==0&&j==3)continue;
                int k=i+way[j];
                if(!flag[k])continue;
                mat[i][k]=-1;
            }
        }
        if(!FLAG){printf("-1\n");continue;}
        gauss(n*m,n*m);
        printf("%.6lf\n",ans[S]);
    }
}
