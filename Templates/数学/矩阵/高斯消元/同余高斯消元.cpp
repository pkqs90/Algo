//Poj 2947 - Widget Factory
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
int a[401][401],ans[401];
int go(string c){
    if(c=="MON")return 0;
    if(c=="TUE")return 1;
    if(c=="WED")return 2;
    if(c=="THU")return 3;
    if(c=="FRI")return 4;
    if(c=="SAT")return 5;
    if(c=="SUN")return 6;
}
void gauss(int n,int m){
    //n��mΪϵ������Ĵ�С
    int i,j,k;
    for(i=0,j=0;i<n&&j<m;j++){
        for(k=i;k<n;k++)if(a[k][j])break;
        if(k<n){
            for(int r=0;r<=m;r++)swap(a[i][r],a[k][r]);
            //����ӵ�i+1�п�ʼ���Ϳ�����..ֻҪ��֤���н��ݾͿ���
            for(int r=i+1;r<n;r++)
                if(a[r][j]){
                    int b1=a[i][j],b2=a[r][j];
                    for(int t=0;t<=m;t++)
                        a[r][t]=((b1*a[r][t]-b2*a[i][t])%7+7)%7;
                }
            i++;
        }
    }//�ж��޽�һ��Ҫ�����..
    for(int r=i;r<n;r++)if(a[r][m]!=0){
        printf("Inconsistent data.\n");
        return;
    }
    if(i<m){
        printf("Multiple solutions.\n");
        return;
    }
    //��m-1��ʼ����Ϊ���һ����Ψһ��Ļ�һ����һ���ϸ�ĵ�������ʽ..
    for(int r=m-1;r>=0;r--){
        int tmp=0;
        for(int t=r+1;t<m;t++)
            tmp+=a[r][t]*ans[t],tmp%=7;
        while((a[r][m]-tmp)%a[r][r])a[r][m]+=7;
        //�����ܹ���ô����ԭ����7��һ������..��˱�֤����ô��һ��������6��֮�ڼӳ�һ������..
        ans[r]=(a[r][m]-tmp)/a[r][r],ans[r]=(ans[r]%7+7)%7;
    }
    for(int i=0;i<m;i++){
        if(ans[i]<3)ans[i]+=7;
        printf("%d%s",ans[i],i==m-1?"\n":" ");
    }
}
int n,m,k,x;
char ch1[10],ch2[10];
int main(){
    while(scanf("%d%d",&n,&m)==2){
        if(!n&&!m)break;
        memset(a,0,sizeof(a));
        for(int i=0;i<m;i++){
            scanf("%d %s %s",&k,&ch1,&ch2);
            int days=(go(ch2)-go(ch1)+1+7)%7;
            a[i][n]=days;
            while(k--){
                scanf("%d",&x),x--,a[i][x]++;
                if(a[i][x]>=7)a[i][x]-=7;
            }
        }
        gauss(m,n);
    }
}
