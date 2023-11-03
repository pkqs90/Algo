//maintain(北京集训队)
#include <iostream>
#include <math.h>
#include <stdio.h>
#define  maxn 1000005
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
using namespace std;
struct seg_tree{int l,r;int mid(){return l+r>>1;}}seg[4*maxn];
struct splay{int l,r,f,size,key;}tree[4*maxn];
int n,m,color[maxn],prev[maxn],temp[maxn],root[4*maxn],tree_size;
/*void pushdown(int x){
     //平衡树的标记下传和线段树一样,在给一个节点表上标记后同时对这个节点进行值的修改
     //理论上说每次操作都要pushdown的,但如果每次操作之前都先进行提根的splay操作的话就不用刻意pushdown了..因此pushdown可以只在splay和update函数中用到
     if(tree[x].rev){
        if(tree[x].l){
           tree[tree[x].l].rev ^= 1;
           swap(tree[tree[x].l].l,tree[tree[x].l].r);
           swap(tree[tree[x].l].lmax,tree[tree[x].l].rmax);
        }
        if(tree[x].r){
           tree[tree[x].r].rev ^= 1;
           swap(tree[tree[x].r].l,tree[tree[x].r].r);
           swap(tree[tree[x].r].lmax,tree[tree[x].r].rmax);
        }
        tree[x].rev = 0;
     }
     if(tree[x].mark){
        if(tree[x].l){
           tree[tree[x].l].key = tree[x].key, tree[tree[x].l].mark = true;
           tree[tree[x].l].sum = tree[tree[x].l].size * tree[tree[x].l].key;
           tree[tree[x].l].max = tree[tree[x].l].lmax = tree[tree[x].l].rmax = tree[tree[x].l].key < 0 ? tree[tree[x].l].key: tree[tree[x].l].sum;
        }
        if(tree[x].r){
           tree[tree[x].r].key = tree[x].key, tree[tree[x].r].mark = true;
           tree[tree[x].r].sum = tree[tree[x].r].size * tree[tree[x].r].key;
           tree[tree[x].r].max = tree[tree[x].r].lmax = tree[tree[x].r].rmax = tree[tree[x].r].key < 0 ? tree[tree[x].r].key: tree[tree[x].r].sum;
        }
        tree[x].mark=0;
     }
}*/
void update(int x){
     pushdown(x);
     tree[x].size=tree[tree[x].l].size+tree[tree[x].r].size+1;
}
void zig(int x){
     int y=tree[x].f,z=tree[y].f,A=tree[x].r;
     pushdown(y),pushdown(x);
     if(tree[z].l==y)tree[z].l=x;
     else tree[z].r=x;
     tree[x].f=z,tree[y].f=x;
     tree[y].l=A,tree[x].r=y;
     if(A)tree[A].f=y;
     update(y);
}
void zag(int x){
     int y=tree[x].f,z=tree[y].f,A=tree[x].l;
     pushdown(y),pushdown(x);
     if(tree[z].l==y)tree[z].l=x;
     else tree[z].r=x;
     tree[x].f=z,tree[y].f=x;
     tree[y].r=A,tree[x].l=y;
     if(A)tree[A].f=y;
     update(y);
}
void splay(int x){
     int y=tree[x].f,z=tree[y].f;
     //这里不用root=x,每次进行splay后最后再改变root..
     while(y){
        pushdown(x);
        if(!z){
           if(x==tree[y].l)zig(x);
           else zag(x);
           break;
        }
        if(x==tree[y].l&&y==tree[z].l)
           zig(y),zig(x);
        else if(x==tree[y].l&&y==tree[z].r)
           zig(x),zag(x);
        else if(x==tree[y].r&&y==tree[z].r)
           zag(y),zag(x);
        else
           zag(x),zig(x);
        y=tree[x].f,z=tree[y].f;
     }update(x);
}
void insert(int &x,int key,int father){
     //lgn建立节点的正确姿势
     //如果是利用splay对一条链的性质的话则这个insert完全用不上..
     if(!x){
        tree_size++;
        tree[tree_size].f=father,tree[tree_size].key=key,tree[tree_size].size=1;
        x=tree_size;
        return;
     }
     if(key<=tree[x].key)insert(tree[x].l,key,x);
     else insert(tree[x].r,key,x);
     update(x);
}
int find(int x,int key){
    //找小于key的节点个数(小于等于key-1的节点个数)
    int temp=0;key--;
    while(x){
       if(key>=tree[x].key)temp+=tree[tree[x].l].size+1,x=tree[x].r;
       else x=tree[x].l;
    }
    return temp;
}
int Find(int x,int M){
    //找排名M的数
     while(1){
        if(tree[tree[x].l].size == M-1)break;
        if(tree[tree[x].l].size < M)
           M -= (tree[tree[x].l].size+1), x = tree[x].r;//这里要注意多减一个1
        else
           x = tree[x].l;
     }
     return x;
}
void erase(int &X,int key){
     //删除一个节点值为key的节点
     int x=X;
     while(1){
        if(key==tree[x].key)break;
        if(key<tree[x].key)x=tree[x].l;
        else x=tree[x].r;
     }
     splay(x);
     if(!tree[x].l){
        tree[tree[x].r].f=0;
        X=tree[x].r;return;
     }
     int p=tree[x].l;tree[p].f=0;
     while(tree[p].r)p=tree[p].r;
     splay(p);
     //把它左子树的最后节点提上来
     tree[p].r=tree[x].r;
     if(tree[x].r)tree[tree[x].r].f=p;
     update(p);
     X=p;
}
void buildtree(int l,int r,int x){
     seg[x].l=l,seg[x].r=r;
     //splay之后改变root
     for(int i=l;i<=r;i++)
        insert(root[x],prev[i],0),splay(tree_size),root[x]=tree_size;
     if(l==r)return;
     int mid=seg[x].mid();
     buildtree(l,mid,lc(x));
     buildtree(mid+1,r,rc(x));
}
int query(int l,int r,int x){
    if(l<=seg[x].l&&seg[x].r<=r)
       return find(root[x],l);
    int mid=seg[x].mid();
    if(r<=mid)return query(l,r,lc(x));
    else if(l>mid)return query(l,r,rc(x));
    else return query(l,r,lc(x))+query(l,r,rc(x));
}
void change(int pre,int now,int pos,int x){
     erase(root[x],pre);
     insert(root[x],now,0);
     if(seg[x].l==seg[x].r)return;
     int mid=seg[x].mid();
     if(pos<=mid)change(pre,now,pos,lc(x));
     else change(pre,now,pos,rc(x));
}
void cchange(int x,int col){
     int tmp;
     prev[x]=0;
     for(int i=1;i<=n;i++){
        if(prev[i]==x){
           change(x,prev[x],i,1);
           prev[i]=prev[prev[x]];
        }
        if(i<x&&color[i]==col)prev[x]=i;
        if(i>x&&prev[i]<x&&color[i]==col){
           change(prev[i],x,i,1);
           prev[i]=x;
        }
     }
     color[x]=col;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
       scanf("%d",&color[i]);
    for(int i=1;i<=n;i++)
       prev[i]=temp[color[i]],temp[color[i]]=i;
    buildtree(1,n,1);
    char A;int x,y;
    while(m--){
       scanf(" %c%d%d",&A,&x,&y);
       if(A=='Q')printf("%d\n",query(x,y,1));
       else{
          int p=prev[x];
          cchange(x,y),change(p,prev[x],x,1);
       }
    }
    //system("pause");
    return 0;
}
