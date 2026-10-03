#include <bits/stdc++.h>
using namespace std;
#define int long long

int egcd(int a,int b, int &x, int &y) {
    if (b == 0) {x=1;y=0;return a;}
    int x1, y1, g= egcd(b, a%b, x1, y1);
    x = y1; y = x1- a/b*y1;
    return g;
}

int modinv (int a, int m) {
    int x,y;
    int g = egcd(a,m,x,y);
    return x>0?x:x+m;
}

inline int mul (int a,int b,int m) {return ((__uint128_t) a*b )%m;  }

int bigmod (int a, int e, int m) {
    a=a%m;
    int res =1;
    while (e) {
        if (e&1) res=mul(res,a,m);
        a = mul(a,a,m);
        e>>=1;
    }
    return res;
}

bool valid_e (int e, int phi) { return __gcd(e,phi) ==1; }

signed main  () {
    int p = 61;
    int q = 53;
    int n = p*q;
    int phi = (p-1)*(q-1);
    int e = 17;
    cout<<e<<endl;
    int m = 100;
    int c = bigmod(m, e, n);
    int d = modinv(e,phi);
    cout<<d<<endl;

    int m2 = bigmod(c,d,n);
    cout<<m<<endl;
    cout<<c<<endl;
    cout<<m2<<endl;
}
