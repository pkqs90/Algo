#include <iostream>
#include <stdio.h>
#define  ll long long
#define  size 16
using namespace std;

int size;
struct Matrix{
    LL base[88][88];
    void init(){
        memset(base, 0, sizeof(base));
    }
    void init2(){
        init();
        for(int i = 0; i < size; i ++) base[i][i]=1;
    }
    void debug(){
        for(int i = 0; i < size; i ++){
            for(int j = 0; j < size; j ++)
                cout << base[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
    }
}start, trans, temp, ans;

void copy(Matrix &A, Matrix B){
     for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++)
           A.base[i][j] = B.base[i][j];
}
void go(Matrix &A, Matrix B){
    Matrix temp;
    temp.init();
    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++)
            for(int k = 0; k < size; k ++)
                temp.base[i][j] += A.base[i][k] * B.base[k][j],
                temp.base[i][j] %= mod;
    copy(A, temp);
}
void Mul(LL x){
    while(x){
        if(x & 1) go(start, trans);
        go(trans, trans);
        x >>= 1;
    }
}

void dfs(int k,int p,int now,int next){
     if(now==15){
        trans.base[k][next]=1;
        return;
     }
     while(now&(1<<p))p++;
     if(p<=2 && !(now&(1<<p)) && !(now&(1<<(p+1))))
        dfs(k,p+2,now|(1<<p)|(1<<(p+1)),next);
     if(p<=3 && !(now&(1<<p)) && !(next&(1<<p)))
        dfs(k,p+1,now|(1<<p),next|(1<<p));
}
int main(){
    ans.base[0][0]=1;
    for(int i=0;i<16;i++)
       dfs(i,0,i,0);
    while(scanf("%d%d",&n,&mod)&&n&&mod){
       copy(trans,temp);
       start.init2();
       multiply(n);
       go(start,ans);
       printf("%d\n",start.base[0][0]);
    }
    system("pause");
    return 0;
}
