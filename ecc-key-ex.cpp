#include <bits/stdc++.h>
#include <cassert>
#define int long long
using namespace std;

const int a_ = 2, b_ = 4, p = 7;

int mod(int a) {
  int r = a % p;
  return r < 0 ? r + p : r;
}

int mod_mul(int a, int b) { return mod((__int128_t)a * b); }

int eval(int x) {
  int cand = x * x * x + a_ * x + b_;
  cand = cand % p;
  for (int i = 0; i < p; i++) {
    if (mod_mul(i, i) == cand)
      return i;
  }
  return -1;
}

int mod_pow(int a, int e) {
  a %= p;
  int res = 1;
  while (e) {
    if (e & 1)
      res = mod_mul(res, a);
    a = mod_mul(a, a);
    e >>= 1;
  }
  return res;
}

int mod_inv(int a) { return mod_pow(a, p - 2); }

struct Point {
  int x, y;
  bool inf = false;
  Point() : inf(true) {}
  Point(int x, int y) : x(mod(x)), y(mod(y))
  {}
};

Point add(Point a, Point b) {
  if (a.inf) return b;
  if (b.inf) return a;
  int lambda_nom, lambda_den;
  if (a.x == b.x) {
    if (a.y == b.y) {   // dbl
        lambda_nom = 3 * a.x * a.x + a_;
        lambda_den = 2 * a.y;
    }
    else if ((a.y + b.y) % p == 0) { return Point(); }//inf
    else { /*no need to handle , impossible case*/}
  } else {
    lambda_nom = b.y - a.y;
    lambda_den = b.x - a.x;
  }
  if (lambda_den == 0) return Point();
  int lambda = mod_mul(lambda_nom, mod_inv(lambda_den));

  int x3 = mod_mul(lambda, lambda) - a.x - b.x;
  int y3 = mod_mul(lambda, (a.x - x3)) - a.y;
  return Point(x3, y3);
}

Point mul(Point a, int e) {
  Point res = Point();
  while (e) {
    if (e & 1)
      res = add(res, a);
    a = add(a, a);
    e >>= 1;
  }
  return res;
}

signed main() {
    assert(4 * a_ * a_ + 27 * b_ * b_ != 0);
    int x,y;
    for (int x=0;x<p;x++) {
        y = eval(x);
        if (y!=-1) break;
    }
    assert(y!=-1);
    Point g = Point(x,y);
    int a = 2;
    int b = 3;

    Point ag = mul(g,a);
    Point bg = mul(g,b);

    Point agb = mul(ag,b);
    Point bga = mul(bg,a);

    assert(agb.inf == bga.inf);
    assert(agb.x == bga.x);
    assert(agb.y == bga.y);

}
