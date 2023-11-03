//Hoj 3153
#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  100011
#define  maxm  10005
#define  ll    long long
#define  ull   unsigned long long
#define  inf   1e9
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
using namespace std;
double a,w,h;
double F(double x){
    //被积函数
    return sqrt(1+4*a*a*x*x);
}
double simpson(double l,double r){
    double m=(r+l)/2.0;
    return (F(l)+F(r)+4*F(m))*(r-l)/6.0;
}
double asr(double l,double r,double epsilon,double A){
    double m=(r+l)/2.0;
    double L=simpson(l,m),R=simpson(m,r);
    if(fabs(L+R-A)<15*epsilon)return L+R+(L+R-A)/15.0;
    return asr(l,m,epsilon/2.0,L)+asr(m,r,epsilon/2.0,R);
}
double asr(double l,double r,double epsilon){
    return asr(l,r,epsilon,simpson(l,r));
}
double calc(double w,double h){
    a=4.0*h/w/w;
    //上边界,下边界,精度控制
    return asr(0,w/2,eps)*2;
}
int t,cas;
int main(){
    cin>>t;
    while(t--){
        scanf("%lf%lf",&w,&h);
        printf("Case %d:\n%.1lf\n",++cas,calc(w,h));
        if(t)puts("");
    }
}
