//poj 1845

#include <iostream>
#include <stdio.h>
#define  ll   long long
#define  maxn 1000005
#define  mod  9901
using namespace std;

/////////////////////////////////////

int inv[mod];

void init_inv(){
    inv[1] = 1;
    for(int i = 2; i < mod; i ++)
        inv[i] = (mod - mod / i) * (LL) inv[mod % i] % mod;
}

/////////////////////////////////////

ll a,b,p[50005][3],cnt,ans=1;

vector <int> prime;
bool is_prime[MAXN];
void prime_table(){
    for(int i = 0; i < MAXN; i ++) is_prime[i] = true;
    for(int i = 2 ; i < MAXN; i ++){
        if(is_prime[i]) prime.pb(i);
        for(int j = 0; j < prime.size() && i * prime[j] < MAXN; j ++){
            is_prime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

void prime(ll x){
     for(int i=2;i*i<=x;i++)if(x%i==0){
        p[++cnt][1]=i;
        while(x%i==0)p[cnt][2]++,x/=i;
     }
     if(x>1)p[++cnt][1]=x,p[cnt][2]=1;
}//分解质因数

LL pow_mod(LL x, LL y, LL z) {
    LL res = 1;
    while(y) {
       if(y & 1) res *= x, res %= z;
       x *= x, x %= z, y >>= 1;
    }
    return res % z;
}

void ext_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}

LL inv(LL a, LL c) {
    LL d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

int main(){
    cin>>a>>b;
    prime(a);
    for(int i=1;i<=cnt;i++){
       ll temp=1;
       if(p[i][1]%mod!=1){
          temp*=pow_mod(p[i][1],b*p[i][2]+1);
          temp=(temp-1+mod)%mod;
          if(temp==0)temp=mod;
          temp*=inv(p[i][1]-1,mod);
          temp%=mod;
       }
       else{
          temp=(b*p[i][2]+1)%mod;
       }
       ans=(ans*temp)%mod;
    }
    cout<<ans<<endl;
    system("pause");
    return 0;
}
