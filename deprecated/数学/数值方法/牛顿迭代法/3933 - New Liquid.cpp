#pragma  comment(linker, "/STACK:36777216")
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#define  lowbit(x) (x&(-x))
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-8
#define  maxn  10010
#define  maxm  2222
#define  ll    long long
#define  ull   unsigned long long
#define  inf   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000000
using namespace std;

const double g=980;
double alpha;
double v0,f;
int a;

double deriv(double theta,double t){
    return (f*v0*sin(theta)+g*cos(alpha))*exp(-t*f)/f-g*cos(alpha)/f;
}

double func(double theta,double t){
    return -((f*v0*sin(theta)+g*cos(alpha))*(exp(-t*f)-1))/(f*f)-g*cos(alpha)*t/f;
}

double calc(double theta){
    double res=1.0;
    //每个零点的一个范围内的所有数都能够迭代到该零点..
    while(1){
        double y=func(theta,res);
        if(fabs(y)<eps)break;
        else res=res-y/deriv(theta,res);
        //迭代 x 值..写法比较机智..
    }
    return -((f*v0*cos(theta)+g*sin(alpha))*(exp(-res*f)-1))/(f*f)-g*sin(alpha)*res/f;
}

int main(){
    while(scanf("%d%lf%lf",&a,&v0,&f)==3){
        double opt=0.0;
        alpha=(double)a*pi/180.0;
        int ans=0;
        for(int i=1;i<90-a;i++){
            double tt=calc((double)i*pi/180.0);
            if(tt>opt)opt=tt,ans=i;
        }
        printf("%d\n",ans+a);
    }
}
