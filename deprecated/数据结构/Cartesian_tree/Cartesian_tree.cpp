//poj1785

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define  maxn 60005
using namespace std;
int n,tail,root;
struct pnt{int f,l,r,val;char ch[105];}tree[maxn];
bool cmp(const pnt &a,const pnt &b){return strcmp(a.ch,b.ch)<0;}
void init(){
     for(int i=0;i<=n;i++)
        tree[i].f=tree[i].l=tree[i].r=tree[i].val=0;
}
void insert(int x){
     int p=x-1;//因为x-1一定在最右的路径的末端（没有右儿子）
     while(tree[p].val<tree[x].val)p=tree[p].f;
     if(!p)root=x;
     tree[x].l=tree[p].r,tree[tree[p].r].f=x;
     tree[x].f=p,tree[p].r=x;
}
void dfs(int x){
     printf("(");
     if(tree[x].l)dfs(tree[x].l);
     printf("%s/%d",tree[x].ch,tree[x].val);
     if(tree[x].r)dfs(tree[x].r);
     printf(")");
}
int main(){
    while(scanf("%d",&n)==1&&n){
       init();
       for(int i=1;i<=n;i++)
          scanf(" %[a-z]/%d",&tree[i].ch,&tree[i].val);
       sort(tree+1,tree+1+n,cmp);
       tree[root=0].val=0x7fffffff;
       for(int i=1;i<=n;i++)
           insert(i);
       dfs(root);
       printf("\n");
    }
    return 0;
}


