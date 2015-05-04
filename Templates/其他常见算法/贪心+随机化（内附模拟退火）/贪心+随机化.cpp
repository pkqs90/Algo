//不是模拟退火，而是基于一个贪心的随机化算法。 
//poj 1379
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#define  maxn 1005
#define  NUM  20
using namespace std;

struct point{
       double x,y,val;
       point(){}//构造函数名称要和类名称相同 
       point(double _x,double _y){x=_x,y=_y;}//这个就相当于make_pair()了..这里的"_x"不能是"x",否则会傻逼 
}p[maxn],May[NUM+5],temp;
int t,n;
double X,Y;

double Rand(){
       return (double)(rand()%10001)/10000.0;//构造0~1的随机浮点小数..这里可以自己设精度..精度别设太粗..不然会sb.. 
}

double find_val(point A){
       double len=1e10;
       for(int i=1;i<=n;i++)
          len=min(len,sqrt((A.x-p[i].x)*(A.x-p[i].x)+(A.y-p[i].y)*(A.y-p[i].y)));
       return len;
}

point make_point(point A,point B){
      point temp=point(A.x+(B.x-A.x)*Rand(),A.y+(B.y-A.y)*Rand());
      temp.val=find_val(temp);
      return temp; 
}

void Solve(double D){
     May[1]=point(0,0);May[1].val=find_val(May[1]);
     May[2]=point(0,Y);May[2].val=find_val(May[2]);
     May[3]=point(X,0);May[3].val=find_val(May[3]);
     May[4]=point(X,Y);May[4].val=find_val(May[4]);
     for(int i=5;i<=NUM;i++)
        May[i]=make_point(point(0.0,0.0),point(X,Y));
     int cnt=0;
     while(D>0.01){//选0.01是因为答案只用保留到一位小数。 
        for(int i=1;i<=NUM;i++)
           for(int j=1;j<=NUM;j++){
              temp=make_point(point(max(0.0,May[i].x-D),max(0.0,May[i].y-D)),point(min(X,May[i].x+D),min(Y,May[i].y+D)));
              if(temp.val>May[i].val)
                 May[i]=temp;
              /*else{
                 double delta=May[i].val-temp.val,K=0.0001;
                 double possibility=exp(-(delta/(cnt*K)));//K是重要参数。 
                 double Rand=(double)(rand()%1001)/1000;
                 if(Rand<possibility)
                    May[i]=temp;
                 加上这部分就是模拟退火了。不过我不会调参数，所以..再加上这题好像就数学角度而言有个比较好的性质，因此直接贪心就好了.. 
              }*/
           }
           D*=0.5;//这部分就是调整步长，也就是降温速度，0.2估计是因为数据太弱所以过了吧。。改成0.5好了 
        cnt++;//降温次数。 
     }
     point ans;
     ans.val=0;
     for(int i=1;i<=NUM;i++)
        if(May[i].val>ans.val)
           ans=May[i];
     printf("The safest point is (%.1f, %.1f).\n",ans.x,ans.y);
}

int main(){
    //srand(time(0));
    scanf("%d",&t);
    while(t--){
       scanf("%lf%lf%d",&X,&Y,&n);
       for(int i=1;i<=n;i++)
          scanf("%lf%lf",&p[i].x,&p[i].y);
       Solve(max(X,Y));
    }
    system("pause");
    return 0;
}
