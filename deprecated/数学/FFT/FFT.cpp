// HDU 1402 A * B Problem Plus

#include <bits/stdc++.h>

using namespace std;

#define  DB  double

const DB PI = acos(-1);

struct Complex{
    DB a, b;
    Complex(){}
    Complex(DB _a, DB _b){
        a = _a, b = _b;
    }
    Complex operator + (const Complex &c) const {return Complex(a + c.a , b + c.b);}
    Complex operator - (const Complex &c) const {return Complex(a - c.a , b - c.b);}
    Complex operator * (const Complex &c) const {return Complex(a * c.a - b * c.b , a * c.b + b * c.a);}
};

void Change(Complex y[], int len) {
    for(int i = 1 ,j = len / 2; i < len - 1; i ++){
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k)
            j -= k, k /= 2;
        if(j < k) j += k;
    }
}

void FFT(int len, int on, Complex y[]){
    Change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h){
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k ++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t, y[k + h / 2] = u - t, w = w * wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i ++)
            y[i].a = (y[i].a / len);
}

const int N = 1e5 + 7;

char ch1[N], ch2[N];

Complex a[N << 2], b[N << 2];

int res[N << 2];

int main() {
    while (scanf(" %s %s", ch1, ch2) == 2) {
        int l1 = strlen(ch1), l2 = strlen(ch2), len = 1;
        while (len < 2 * max(l1, l2)) len <<= 1;
        for (int i = 0; i < l1; i ++) a[i] = Complex(ch1[l1 - 1 - i] - '0', 0);
        for (int i = l1; i < len; i ++) a[i] = Complex(0, 0);
        for (int i = 0; i < l2; i ++) b[i] = Complex(ch2[l2 - 1 - i] - '0', 0);
        for (int i = l2; i < len; i ++) b[i] = Complex(0, 0);
        FFT(len, 1, a);
        FFT(len, 1, b);
        for (int i = 0; i < len; i ++) a[i] = a[i] * b[i];
        FFT(len, -1, a);
        for (int i = 0; i < len; i ++) res[i] = (a[i].a + 0.5);
        int mx = 0, op = 0;
        for (int i = 0; i < len; i ++) {
            res[i + 1] += res[i] / 10, res[i] %= 10;
            if (res[i]) mx = i;
        }
        for (int i = mx; i >= 0; i --) printf("%d", res[i]);
        puts("");
    }
}
