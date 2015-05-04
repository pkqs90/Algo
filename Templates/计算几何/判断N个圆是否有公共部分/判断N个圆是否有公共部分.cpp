#include <cstdio>
#include <algorithm>
#include <math.h>
#define  maxn 100005
#define  eps  1e-9
using namespace std;
struct point{
   double x,y;
   point(){}
   point(double _x,double _y){x=_x,y=_y;}
}A[maxn];
double R[maxn],left,right;
int N,x,y,r;
bool judge(const point a,double r1,const point b,double r2){
     double l2=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
     if(l2>(r1+r2)*(r1+r2))return false;
     return true;
}
int main(){
    scanf("%d",&N);
    for(int i=0;i<N;i++){
       scanf("%d%d%d",&x,&y,&r);
       A[i]=point(x,y);
       R[i]=r;
       if(!i)left=x-r,right=x+r;
       else left=max(left,(double)(x-r)),right=min(right,double(x+r));
    }
    if(left>=right){
       puts("NO");
       return 0;
    }
    while(right-left>eps){
       double mid=0.5*(right+left);
       int a,b;
       double h,l;
       for(int i=0;i<N;i++){
          double d=sqrt(R[i]*R[i]-(mid-A[i].x)*(mid-A[i].x));
          double u=A[i].y-d,v=A[i].y+d;
          if(i==0||u>l)l=u,a=i;
          if(i==0||v<h)h=v,b=i;
       }
       if(h>l){
          puts("YES");
          return 0;
       }
       if(!judge(A[a],R[a],A[b],R[b])){
          puts("NO");
          return 0;
       }
       if(mid>A[a].x)right=mid;
       else left=mid;
    }
    puts("NO");
    return 0;
}
