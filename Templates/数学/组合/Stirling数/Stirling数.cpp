#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <map>
#include <queue>
#include <algorithm>
#pragma  comment(linker, "/STACK:36777216")
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  pi    (acos(-1))
#define  eps   1e-3
#define  maxn  150005
#define  maxm  10005
#define  ll    long long
#define  inf   1e9
#define  pb    push_back
#define  mod   1000000007
using namespace std;
ll stir1[21][21],stir2[21][21];
int main(){
    stir1[0][0]=1;
    for(int i=1;i<21;i++){
        stir1[i][0]=0;
        for(int j=1;j<=i;j++)
            stir1[i][j]=(i-1)*stir1[i-1][j]+stir1[i-1][j-1];
    }
    stir2[0][0]=1;
    for(int i=1;i<21;i++){
        stir2[i][0]=0;
        for(int j=1;j<=i;j++)
            stir2[i][j]=j*stir2[i-1][j]+stir2[i-1][j-1];
    }
    cout<<"Stirling1"<<endl;
    for(int i=0;i<21;i++){
        ll res=0;
        for(int j=0;j<=i;j++)
            cout << stir1[i][j] << ' ';
        cout << endl;
        //res为A(i,i)..排列数..
    }
    cout<<"Stirling2"<<endl;
    for(int i=0;i<21;i++){
        ll res=0;
        for(int j=0;j<=i;j++)
            cout << stir2[i][j] << ' ';
        cout << endl;
        //res为贝尔数..n个不同的球放入n个相同的箱子
    }
    for(int i=0;i<=6;i++)
        cout<<stir2[20][i]<<endl;
}
