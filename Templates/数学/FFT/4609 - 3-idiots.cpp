#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#define  pi   (acos(-1))
#define  eps  1e-6
#define  maxn 200005
#define  ll   long long
using namespace std;
struct Complex{
    double a,b;
    Complex(){}
    Complex(double _a,double _b):a(_a),b(_b){}
    Complex operator + (const Complex &c) const {return Complex(a + c.a , b + c.b);}
    Complex operator - (const Complex &c) const {return Complex(a - c.a , b - c.b);}
    Complex operator * (const Complex &c) const {return Complex(a * c.a - b * c.b , a * c.b + b * c.a);}
};
void change (Complex y[],int len) {
    for (int i=1,j=len/2;i<len-1;i++) {
        if (i<j)swap(y[i],y[j]);
        int k=len/2;
        while(j>=k)
            j-=k,k/=2;
        if(j<k)j+=k;
    }
}
void fft(int len,int on,Complex y[]){
    change (y,len);
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
Complex a[maxn<<2];
ll ans[maxn<<2],len,s[maxn<<2],mx,t,n,x,pp[maxn<<2],sum[maxn<<2];
void init(){
    memset(ans,0,sizeof(ans));
    memset(s,0,sizeof(s));
    memset(sum,0,sizeof(sum));
    mx=0,len=1;
}
int main(){
    cin>>t;
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&pp[i]);
            s[pp[i]]++,mx=max(mx,pp[i]);
        }
        mx++;//注意fft中是从0到n-1进行的，所以mx要++
        while(len<2*mx)len<<=1;
        for(int i=0;i<mx;i++)a[i]=Complex((double)s[i],0);
        for(int i=mx;i<len;i++)a[i]=Complex(0,0);
        fft(len,1,a);
        for(int i=0;i<len;i++)a[i]=a[i]*a[i];
        fft(len,-1,a);
        for(int i=0;i<len;i++)ans[i]=(ll)(a[i].a+0.5);
        for(int i=1;i<=n;i++)
            ans[2*pp[i]]--;//自己加自己
        for(int i=0;i<len;i++)
            ans[i]/=2;//a+b,b+a重复计算
        for(int i=1;i<len;i++)
            sum[i]=sum[i-1]+ans[i];
        ll cnt=0,tot=(ll)(n)*(ll)(n-1)*(ll)(n-2)/6;
        for(int i=1;i<=n;i++){ // 枚举最长边，另外两条边的 sum 要大于该边
            cnt+=(sum[len-1]-sum[pp[i]]);
            cnt-=(n-1); // 减掉和自己相加
            cnt-=(n-i)*(n-i-1)/2; // 减掉大于自己的两条边相加
            cnt-=(n-i)*(i-1); // 减掉大于 + 小于
        }
        printf("%.7f\n",(double)cnt/tot);
    }
    return 0;
}
