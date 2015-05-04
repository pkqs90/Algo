//Hdu 4200 - Bad Wiring
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
#define  maxn  200005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  mod   1000000007
using namespace std;
int t,n,d,a[105][105],ANS,ans[105];
void dfs(int r,int co,int tot){
    if(tot>ANS)return;
    if(co==-1){
        ANS=min(ANS,tot);return;
    }
    int first;
    for(int i=n-1;i>=0;i--)if(a[r][i])first=i;
    if(co==first){
        ans[first]=a[r][n];
        for(int j=first+1;j<n;j++)
            ans[first]^=(ans[j]*a[r][j]);
        dfs(r-1,first-1,tot+ans[first]);
    }
    else{
        ans[co]=1;dfs(r,co-1,tot+1);
        ans[co]=0;dfs(r,co-1,tot);
    }
}
void gauss(int n,int m){
    //n和m为系数矩阵的大小
    int i,j,k;
    for(i=0,j=0;i<n&&j<m;j++){
        k=i;
        for(;k<n;k++)if(a[k][j])break;
        if(k<n){
            for(int r=0;r<=m;r++)swap(a[i][r],a[k][r]);
            //这里从第i+1行开始消就可以了..只要保证是行阶梯就可以
            for(int r=i+1;r<n;r++)
                if(a[r][j])
                    for(int t=0;t<=m;t++)
                        a[r][t]^=a[i][t];
            i++;
        }
    }//判断无解一定要在最后..
    for(int r=i;r<n;r++)if(a[r][m]!=0){
        printf("impossible\n");
        return;
    }
    dfs(i-1,m-1,0);
    printf("%d\n",ANS);
}
int main(){
    cin>>t;
    while(t--){
        scanf("%d%d",&n,&d);
        memset(a,0,sizeof(a));
        memset(ans,0,sizeof(ans));
        ANS=n;
        for(int i=0;i<n;i++)
            scanf("%d",&a[i][n]);
        for(int i=0;i<n;i++)
            for(int j=max(0,i-d);j<=min(n-1,i+d);j++)
                a[j][i]=1;
        gauss(n,n);
    }
}
