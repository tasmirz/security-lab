#include <bits/stdc++.h>
#include <cassert>
#define int long long
using namespace std;


int egcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int g = egcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - a / b * y1;
  return g;
}

int mod (int a,int m) {
    int r = a%m;
    return r<0?m+r:r;
}

int mod_mul (int a,int b,int p) {
    return  mod((__int128_t)a*b,p);
}

int mod_pow(int a,int e, int p) {
    a%=p;
    int res =1;
    while (e) {
        if (e&1) res = mod_mul(res, a,p);
        a= mod_mul(a, a, p);
        e>>=1;
    }
    return res;
}

int mod_inv(int a,int m) {
    int x,y;
    int g  = egcd(a, m, x, y);
    assert(g==1);
    return mod(x,m);
}


int find_e(int phi) {
    for (int i=2;i<phi;i++) {
        if (__gcd(phi, i)==1) return i;
    }
    assert(false);
}

signed main() {
    int p =61;
    int q =37;
    int n = p*q;
    int phi = (p-1)*(q-1);
    int e = find_e(phi);
    int d = mod_inv(e, phi);

    int m = 10;
    int m2 =2;

    int c = mod_pow(m, e, n);
    int c2 = mod_pow(m2, e, n);

    int cp = mod_mul(c, c2, n);
    int dec = mod_pow(cp, d, n);

    cout<<m*m2<<endl;
    cout<<dec<<endl;
    assert(dec == mod_mul(m, m2, n));

}
