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
        cout<<mp.size()<<endl;
        if (mp.size()==p-1) { return i;}
    }
    assert(false);
}

signed main () {
    int p = 37;
    int g  = find_g(p);
    int a = 11;
    int y =  mod_pow(g, a, p);
    int m = 100;
    int k = rand()%p;
    int c1  = mod_pow(g,k,p); // g^k %p
    int c2 =  mod_mul(m,mod_pow(y, k,p),p); // c2 =  m*y^k mod p

    int k_ = rand()%p;
    int c1_ = mod_mul(c1,mod_pow(g,k_,p),p);  // c1_ =  c1 * g^k mod p
    int c2_ =  mod_mul(c2,mod_pow(y, k_,p),p); // c2 =  m*y^k mod p

    int dec = mod_mul(c2,mod_inv(mod_pow(c1, a,p),p),p); // dec = c2/(c1^a) mod p
    int dec_ = mod_mul(c2_,mod_inv(mod_pow(c1_, a,p),p),p); // dec = c2/(c1^a) mod p

    assert(dec == dec_);
    assert(m%p == dec_);

    cout<<m%p<<endl;
    cout<<dec_<<endl;
};
