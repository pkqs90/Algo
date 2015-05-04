#include <iostream>
#include <stdio.h>
#define  maxn 50010
using namespace std;
int smin[maxn][21],smax[maxn][21],a[maxn],log[maxn];
int main()
{
    int q,x,y,n,temp;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
       scanf("%d",&a[i]);
       smin[i][0]=a[i];
       smax[i][0]=a[i];
    }
    for(int i=2;i<=n;i++)
       log[i]=log[i/2]+1;
    for(int i=1;i<=log[n];i++)
       for(int j=1;j+(1<<(i-1))<=n;j++)
             smin[j][i]=min(smin[j][i-1],smin[j+(1<<(i-1))][i-1]),
             smax[j][i]=max(smax[j][i-1],smax[j+(1<<(i-1))][i-1]);
    while(q--){
       scanf("%d%d",&x,&y);
       temp=log[y-x+1];
       printf("%d\n",max(smax[x][temp],smax[y-(1<<temp)+1][temp])-min(smin[x][temp],smin[y-(1<<temp)+1][temp]));
    }
    system("pause");
    return 0;
}
