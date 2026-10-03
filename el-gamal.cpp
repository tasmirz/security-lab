#include  <bits/stdc++.h>

#define int long long
using  namespace std;

int mul (int a,int b, int m) {
     return ((__int128_t)a*b)%m;
 }

int bigmod(int a, int e, int m) {
    a =  a%m;
    int res =1;
    while (e) {
        if (e&1) { res = mul(res,a,m);}
        a = mul(a,a,m);
        e>>=1;
    }
    return res;
}

int egcd (int a, int b , int & x, int & y) {
    if (b == 0) { x=1; y=0; return a;}
    int x1, y1;
    int g = egcd(b,b%a,x1,y1);
    x = y1;
    y = x1 - (a/b)*y1 ;
    return  g;
}


int modinv (int a, int m) {
    // int x,y;
    // int g = egcd(a,m,x,y);
    // return x<0?x+m:x;
    return bigmod(a, m-2, m);
}

bool check_primitive (int g, int p ) {
    map<int,signed> mp;
    for (int i=1;i<p;i++) {
        mp[bigmod(g,i,p)] = 1;
    }
    if (mp.size() == p-1) return true;
    return false;
}

signed main () {
    int p =61;
    int g = 2l;
    int m =10;
    int k =10;
    int a = 5;
    int y = bigmod(g, a, p);
    int c1 = bigmod(g, k , p);
    int c2 = m * bigmod(y, k, p) % p;
    int mp = c2 * modinv(bigmod(c1,a, p), p) %p;
    cout<<mp<<endl;
}
