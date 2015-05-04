//FFT处理大数乘法
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#include <complex>
#include <algorithm>
#define  pi  (acos(-1))
#define  eps 1e-6
#define  I   complex <double> (0,1)
using namespace std;
void fft(int len,int sig,complex<double>a[]){
    for(int j=1;j<len-1;j++){
        int i=0;
        for(int k=1,tmp=j;k<len;i=(i<<1)|(tmp&1),k<<=1,tmp>>=1);
        if(j<i)swap(a[i],a[j]);
    }
    for(int m=2;m<=len;m<<=1){
        int mh=m>>1;
        for(int i=0;i<mh;i++){
            complex<double>w=exp(sig*i*pi/mh*I);
            for(int j=i;j<len;j+=m){
                int k=j+mh;
                complex<double>u=a[j];
                a[j]=u+a[k]*w;
                a[k]=u-a[k]*w;
            }
        }
    }
    if(sig==-1)
        for(int i=0;i<len;i++)
            a[i].real()=(int)(a[i].real()/len+eps);
}
complex<double> a[200000],b[200000];
char a1[100010],a2[100010];
int ans[200010];
void init(){
    memset(ans,0,sizeof(ans));
}
int main(){
    while(scanf("%s%s",a1,a2)!=EOF){
        init();
        int l1=strlen(a1),l2=strlen(a2),len=1;
        //这里的l1和l2都是0~l1-1, 0~l2-1，符合FFT中0~n-1的要求
        while(len<2*max(l1,l2))len<<=1;
        for(int i=0;i<l1;i++)a[i]=complex<double>(a1[l1-1-i]-'0',0);
        for(int i=0;i<l2;i++)b[i]=complex<double>(a2[l2-1-i]-'0',0);
        for(int i=l1;i<len;i++)a[i]=complex<double>(0,0);
        for(int i=l2;i<len;i++)b[i]=complex<double>(0,0);
        fft(len,1,a),fft(len,1,b);//1代表求值
        for(int i=0;i<len;++i)a[i]*=b[i];
        fft(len,-1,a);//-1代表插值
        int high=0;
        for(int i=0;i<len;i++){
            ans[i]+=a[i].real();
            if(ans[i])
                high=i;
            ans[i+1]=ans[i]/10;
            ans[i]%=10;
        }
        for(int i=high;i>=0;i--)
            printf("%d",ans[i]);
        printf("\n");
    }
    return 0;
}
