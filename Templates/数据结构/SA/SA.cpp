#include <iostream>
#include <stdio.h>
#include <string.h>
#define maxn 20005
using namespace std;
int wa[maxn],wb[maxn],S[maxn],sa[maxn],rank[maxn],height[maxn];
int cc[maxn],c[maxn],N,l,r;
void da(int n,int m)
{
     memset(wa,0,sizeof(wa)),memset(wb,0,sizeof(wb));
     memset(rank,0,sizeof(rank)),memset(sa,0,sizeof(sa));
     memset(height,0,sizeof(height)),memset(S,0,sizeof(S));
     int i,j,p=0,*X=wa,*Y=wb;//这里写成指针式为了直接交换。。= = 
     for(i=0;i<m;i++) S[i]=0;//初始化ws数组 
     for(i=0;i<n;i++) S[X[i]=c[i]]++;//基数排序第一关键字 
     for(i=1;i<m;i++) S[i]+=S[i-1];//真他妈巧妙！！！ 
     for(i=n-1;i>=0;i--) sa[--S[X[i]]]=i;//我操！！！ 这个基数排序绝了。。
     //这里往上是最初的基数排序。 
     for(j=1;p<n;j*=2,m=p)
     {
       //j是用来倍增的量 
       for(p=0,i=n-j;i<n;i++) Y[p++]=i;
       for(i=0;i<n;i++) if(sa[i]>=j) Y[p++]=sa[i]-j;
       //========================================
       for(i=0;i<m;i++) S[i]=0;
       for(i=0;i<n;i++) S[X[Y[i]]]++;
       for(i=1;i<m;i++) S[i]+=S[i-1];
       for(i=n-1;i>=0;i--) sa[--S[X[Y[i]]]]=Y[i];
       //========================================
       swap(X,Y);
       for(p=1,X[sa[0]]=0,i=1;i<n;i++)
          X[sa[i]]=(Y[sa[i-1]]==Y[sa[i]]&&Y[sa[i-1]+j]==Y[sa[i]+j])?p-1:p++;
     }
     return;
}
void calheight(int n)
{
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1];c[i+k]==c[j+k];k++);
     return;//利用height[rank[i]]>=height[rank[i-1]]-1的性质..注意，这里的==号不能改，改了就不满足height[rank[i]]的性质了！ 
}
bool judge(int K){//按照height进行分组 
     int tempmin=maxn,tempmax=0,temp=0;
     for(int i=1;i<=N;i++){
        tempmin=min(tempmin,sa[i]);
        tempmax=max(tempmax,sa[i]);
        if(height[i+1]<K)
           temp=max(temp,tempmax-tempmin),
           tempmin=maxn,tempmax=0;
     }
     return temp>=K;
}
int main()
{
    while(scanf("%d",&N)&&N){
       memset(c,0,sizeof(c));
       memset(cc,0,sizeof(cc));
       for(int i=0;i<N;i++)
          scanf("%d",&cc[i]);
       for(int i=0;i<N-1;i++)
          c[i]=cc[i+1]-cc[i]+100;
       N--;
       da(N+1,300),calheight(N);//注意这里一定要是n+1,n或n+2都不可..因为不可以有两个end;后面则是calheight(N) 
       l=0,r=N;
       while(l<r){
          int mid=l+r+1>>1;
          if(judge(mid))l=mid;
          else r=mid-1;
       }
       printf("%d\n",l+1>=5?l+1:0);
    }
    system("pause");
    return 0;
}
