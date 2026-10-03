#include <bits/stdc++.h>
#include <cassert>
#define int long long
using namespace std;


int mod_mul (int a, int b,int p) {
    return ((__int128_t)a*b)%p;
}

int mod(int a, int m) {
    int r =  a%m;
    return r<0?m+r:r;
}

int egcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x =  1;
        y = 0;
        return a;
    }
    int x1,y1;
    int g = egcd(b,a%b,x1,y1);
    x = y1;
    y =  x1  - a/b*y1;
    return g;
}

int mod_inv(int a, int m) {
    int x,y;
    int g = egcd(a,m,x,y);
    assert(g==1);
    return mod(x,m);
}

int mod_pow (int a,int e,int m) {
    a%=m;
    int res=1;
    while (e) {
        if (e&1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        e>>=1;
    }
    return res;
}

int mod_inv_2(int a, int m) {
    return mod_pow(a, m-2, m);
}

int find_g (int p) {
    for (int i=2;i<p;i++) {
        map<int,int> mp;
        for (int j=1;j<p;j++) {
            mp[j]=mod_pow(i, j, p);
        }
        if (mp.size()==p-1) { return i;}
    }
    assert(false);
}

signed main () {
    int p = 37;
    int g  = find_g(p);
    int a = 11;
    int y =  mod_pow(g, a, p);
    int m = 10;
    int k = rand()%p;
    int c1  = mod_pow(g,k,p); // g^k %p
    int c2 =  mod_mul(m,mod_pow(y, k,p),p); // c2 =  m*y^k mod p


    int m_ = 2;
    int k_ = rand()%p;
    int c1_  = mod_pow(g,k_,p); // g^k %p
    int c2_ =  mod_mul(m_,mod_pow(y, k_,p),p); // c2 =  m*y^k mod p

    int c1f =  mod_mul(c1,c1_,p);
    int c2f =  mod_mul(c2,c2_,p);

    int d = mod_mul(mod_inv(mod_pow(c1f,a,p),p),c2f,p);
    assert(d == m*m_);
};
