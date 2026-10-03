#include <bits/stdc++.h>
#include <cassert>
#define int long long
using namespace std;

int egcd(int a,int b,int &x, int &y) {
    if (b==0) {
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int g= egcd(b,a%b,x1,y1);
    x = y1;
    y = x1 - a/b*y1;
    return g;
}

int mod (int a,int m) {
    int r =  a%m;
    return r<0?m+r:r;
}

int mod_inv (int a, int m) {
    int x,y;
    int g= egcd(a,m,x,y);
    assert(g==1);
    return mod(x,m);
}


int mod_mul (int a, int b, int m) {
    return mod((__int128_t) a*b,m);
}

int mod_pow(int a, int e, int m) {
    a= mod(a,m);
    int res =1;
    while (e) {
        if (e&1) res = mod_mul(res, a, m);
        a =  mod_mul(a, a, m);
        e>>=1;
    }
    return res;
}

int find_e(int phi) {
    for (int i=2;i<phi;i++) {
        if (__gcd(i,phi)==1) return i;
    }
    assert(false);
}

signed main () {
    int p = 61;
    int q = 11;
    int n = p* q;
    int phi = (p-1)*(q-1);
    int e =  find_e(phi);
    int d = mod_inv(e, phi);

    int m=100;
    int s =  mod_pow(m, d, n);
    int v = mod_pow(s, e, n);
    assert(v==m);
}
