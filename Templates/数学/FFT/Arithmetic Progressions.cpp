#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-3
#define  maxn  50005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  mod   10007
using namespace std;
struct Complex{
    double a,b;
    Complex(double _a=0.0,double _b=0.0):a(_a),b(_b){}
    Complex operator + (const Complex &c) const {return Complex(a + c.a , b + c.b);}
    Complex operator - (const Complex &c) const {return Complex(a - c.a , b - c.b);}
    Complex operator * (const Complex &c) const {return Complex(a * c.a - b * c.b , a * c.b + b * c.a);}
};
void change(Complex y[],int len) {
    for (int i=1,j=len/2;i<len-1;i++) {
        if (i<j)swap(y[i],y[j]);
        int k=len/2;
        while(j>=k)
            j-=k,k/=2;
        if(j<k)j+=k;
    }
}
void fft(int len,int on,Complex y[]){
    change(y,len);
    for (int h=2;h<=len;h<<=1) {
        Complex wn(cos(-on*2*pi/h),sin(-on*2*pi/h));
        for (int j=0;j<len;j+=h){
            Complex w(1,0);
            for (int k=j;k<j+h/2;k++) {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t,y[k+h/2]=u-t,w=w*wn;
            }
        }
    }
    if(on==-1)
        for(int i=0;i<len;i++)
            y[i].a=(y[i].a/len);
}
Complex a[100005],b[100005];
int x[100005],after[30005],before[30005],in[30005],n,mn,mx;
ll res;
int main(){
    cin>>n;
        mn=50000,mx=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&x[i]);
            if(mn>x[i])mn=x[i];
            if(mx<x[i])mx=x[i];
            after[x[i]]++;
        }
        res=0;
        int block=min(n,40);
        int size=(n+block)/block;
        for(int bk=1;bk<=block;bk++){
            int st=1+(bk-1)*size,ed=min(size*bk,n);
            for(int i=st;i<=ed;i++)
                after[x[i]]--;
            for(int i=st;i<=ed;i++){
                for(int j=i+1;j<=ed;j++){
                    if(2*x[i]-x[j]>=0&&2*x[i]-x[j]<=30000){
                        res+=in[2*x[i]-x[j]];
                        res+=before[2*x[i]-x[j]];
                    }
                    if(2*x[j]-x[i]>=0&&2*x[j]-x[i]<=30000)
                        res+=after[2*x[j]-x[i]];
                }
                in[x[i]]++;
            }
            if(bk>1&&bk<block){
                int len=1;
                while(len<2*(mx+1))len<<=1;//×¢ÒâÊÇ mx+1 ..
                for(int i=0;i<=len;i++)
                    a[i]=Complex(0,0),b[i]=Complex(0,0);
                for(int i=mn;i<=mx;i++)
                    a[i]=Complex(before[i],0),b[i]=Complex(after[i],0);
                fft(len,1,a),fft(len,1,b);
                for(int i=0;i<len;i++)a[i]=a[i]*b[i];
                fft(len,-1,a);
                for(int i=st;i<=ed;i++)
                    res+=(ll)(a[2*x[i]].a+0.5);
            }
            for(int i=st;i<=ed;i++)
                before[x[i]]++,in[x[i]]--;
        }
        printf("%lld\n",res);
}
