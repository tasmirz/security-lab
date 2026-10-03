#include  <bits/stdc++.h>
#include <cassert>
#define int long long
using  namespace std;

struct Space {
    int p;
    int a;
    int b;
    Space (int a,int b, int p) :a(a),b(b),p(p) {
        assert(4*a*a*a + 27*b*b != 0);
    }
    int operator()(int x) {
        return x*x*x + a*x + b;
    }
};


int  bigmod (int a,int e, int p) {
    a = a%p;
    int res = 1;
    while (e) {
        if (e & 1) res = (__int128_t) (__int128_t)res*a%p;
        a = (__int128_t)a*a%p;
        e>>=1;
    }
    return res;
}

int modinv (int a,int m) {
    return bigmod(a,m-2,m);
}


int mod(int a, int m) {
    a %= m;
    if (a < 0) a += m;
    return a;
}

int mod_mul(int a, int b, int m) {
    return (__int128_t)mod(a, m) * mod(b, m) % m;
}

int mod_div(int a, int b, int m) {
    return mod_mul(a, modinv(b, m), m);
}

template<Space & s>
struct Point {
    int x=0,y=0;
    bool inf = true;
    Point() {}
    Point(int x,int y) :inf(false) {
        this->x = x%s.p;
        this->y = y%s.p;
    }
    Point operator +(Point t) {
        if (inf) return Point<s>(t); //identity
        if (t.inf ) return Point<s>(*this);
        int lambda;
        if (x == t.x) {
            if (y == -t.y) return Point<s>(); // inf case
            else { //double
                int nom  = 3*x*x + s.a;
                int den =  2*y;
                lambda = mod_div(nom, den, s.p);
            }
        } else {
            int nom  = y - t.y;
            int den =  x - t.x;
            lambda = mod_div(nom, den, s.p);
        }
        int x3 =  mod_mul(lambda,lambda,s.p) -x -t.x;
        int y3 = mod_mul(lambda, (x - x3),s.p) - y;
        return  Point<s>(x3,y3);
    }
    friend Point operator*(int t,Point d) {
        d.x = d.x%s.p;
        d.y = d.y%s.p;
        Point res = Point<s>();
        while (t) {
            if (t & 1) res = res+d;
            d = d+d;
            t--;
        }
        return res;
    }
    friend ostream& operator<<(ostream& out, const Point& p) {
        if (p.inf) {
            return out << "O";
        }

        return out << "(" << p.x << ", " << p.y << ")";
    }

};


Space s(1,2,9);
signed main () {
    Point<s> a(1,s(1));
    a= a+a;
    cout<<a;
}
