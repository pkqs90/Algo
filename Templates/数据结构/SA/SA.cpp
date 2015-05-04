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
     int i,j,p=0,*X=wa,*Y=wb;//����д��ָ��ʽΪ��ֱ�ӽ�������= = 
     for(i=0;i<m;i++) S[i]=0;//��ʼ��ws���� 
     for(i=0;i<n;i++) S[X[i]=c[i]]++;//���������һ�ؼ��� 
     for(i=1;i<m;i++) S[i]+=S[i-1];//������������� 
     for(i=n-1;i>=0;i--) sa[--S[X[i]]]=i;//�Ҳ٣����� �������������ˡ���
     //��������������Ļ������� 
     for(j=1;p<n;j*=2,m=p)
     {
       //j�������������� 
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
     return;//����height[rank[i]]>=height[rank[i-1]]-1������..ע�⣬�����==�Ų��ܸģ����˾Ͳ�����height[rank[i]]�������ˣ� 
}
bool judge(int K){//����height���з��� 
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
       da(N+1,300),calheight(N);//ע������һ��Ҫ��n+1,n��n+2������..��Ϊ������������end;��������calheight(N) 
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
