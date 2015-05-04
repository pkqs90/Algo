#include <iostream>
#include <stdio.h>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  maxn 150005
using namespace std;
struct seg_tree{int l,r,s,mark,xo;int mid(){return l+r>>1;}}tree[maxn<<2];
int x,y;
void init_tree(int l,int r,int x){
     tree[x].l=l,tree[x].r=r;
     tree[x].mark=0;
     if(l==r)return;
     int mid=tree[x].mid();
     init_tree(l,mid,lc(x));
     init_tree(mid+1,r,rc(x));
}
void pushdown(int x){
     if(tree[x].mark){
        tree[lc(x)].mark=tree[rc(x)].mark=tree[x].mark;
        tree[lc(x)].s=tree[rc(x)].s=tree[x].mark-1;
        tree[lc(x)].xo=tree[rc(x)].xo=0;
     }
     if(tree[x].xo){
        tree[lc(x)].s^=1,tree[rc(x)].s^=1;
        tree[lc(x)].xo^=1,tree[rc(x)].xo^=1;
     }
     tree[x].xo=0;
     tree[x].mark=0;
}
void insert(int l,int r,int x,int mark1,int xor1){
     if(tree[x].l>=l&&tree[x].r<=r){
        if(mark1)
           tree[x].xo=0,tree[x].mark=mark1,tree[x].s=mark1-1;
        if(xor1)
           tree[x].xo^=1,tree[x].s^=1;
        return;
     }
     pushdown(x);
     int mid=tree[x].mid();
     if(l<=mid)insert(l,r,lc(x),mark1,xor1);
     if(r>mid)insert(l,r,rc(x),mark1,xor1);
}
bool query(int p,int x){
     if(tree[x].l==tree[x].r)
        return tree[x].s;
     pushdown(x);
     int mid=tree[x].mid();
     if(p<=mid)return query(p,lc(x));
     else return query(p,rc(x));
}
void output(int x,int y){
     char C1,C2;
     if(x%2==0)C1='[';
     else C1='(',x--;
     if(y%2==0)C2=']';
     else C2=')',y++;
     x/=2,y/=2;
     printf("%c%d,%d%c",C1,x,y,C2);
}
int main(){
    init_tree(1,maxn,1);
    char c1,c2,c3;
    while(scanf("%c %c%d,%d%c\n",&c1, &c2, &x, &y, &c3)==5){
       x=(c2=='[')?2*x:2*x+1;
       y=(c3==']')?2*y:2*y-1;
       x+=2,y+=2;
       //第四位参数:2表示+1,1表示-1;第五位参数:0不动,1取反 
       if(x>y){
          if(c1=='I' || c1=='C')insert(0,maxn,1,1,0);
          continue;
       }
       if(c1=='U')insert(x,y,1,2,0);
       if(c1=='I')insert(0,x-1,1,1,0),insert(y+1,maxn,1,1,0);
       if(c1=='D')insert(x,y,1,1,0);
       if(c1=='C')insert(0,x-1,1,1,0),insert(y+1,maxn,1,1,0),insert(x,y,1,0,1);
       if(c1=='S')insert(x,y,1,0,1);
    }
    int flag=0,head=0,tail=0,CNT=0;
    for(int i=2;i<=2*65550;i++)
       if(query(i,1)){
          if(!flag){
             head=tail=i-2,flag=1;
             if(CNT)printf(" ");
          }
          else tail=i-2;
       }
       else if(flag){
          output(head,tail),flag=head=tail=0;
          CNT++;
       }
    if(!CNT)printf("empty set");
    printf("\n");
    return 0;
}
