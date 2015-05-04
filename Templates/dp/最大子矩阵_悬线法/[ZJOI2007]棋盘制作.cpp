#include <iostream>
#include <stdio.h>
#include <string.h>
#define  maxn 2005
using namespace std;
bool a[maxn][maxn];
int up[maxn],lef[maxn][maxn],righ[maxn][maxn];
int n,m,ans,ans2,k;
void go(int p){
    memset(up,0,sizeof(up)),memset(lef,0,sizeof(lef)),memset(righ,0,sizeof(righ));
    for(int i=1;i<=n;i++){
        k=0;
        for(int j=1;j<=m;j++){
            if(a[i][j]==p){
                up[j]++;
                lef[i][j]=max(lef[i-1][j],k+1);
            }
            else
                up[j]=0,k=j,lef[i][j]=0;
        }
        k=m+1;
        for(int j=m;j>=1;j--){
            if(a[i][j]==p){
                righ[i][j]=min(righ[i-1][j],k-1);
                ans=max(ans,up[j]*(righ[i][j]-lef[i][j]+1));
                ans2=max(ans2,min(up[j],righ[i][j]-lef[i][j]+1));
            }
            else
                k=j,righ[i][j]=m+1;;
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            if((i+j)&1)a[i][j]^=1;
        }
    go(1),go(0);
    printf("%d\n%d\n",ans2*ans2,ans);
    return 0;
}
