//poj 1674

#include <iostream>
#include <stdio.h>
using namespace std;
int a[10005],t,n,cnt;
bool flag[10005];
int main(){
    cin>>t;
    while(t--){
       cin>>n;
       cnt=0;
       memset(flag,0,sizeof(flag));
       for(int i=1;i<=n;i++)
          scanf("%d",&a[i]);
       for(int i=1;i<=n;i++)if(!flag[i]){
          int j=i;cnt++;
          do{flag[j]=true,j=a[j];}while(j!=i);
       }
       cout<<n-cnt<<endl;
    }
    system("pause");
    return 0;
}
