#include <bits/stdc++.h>
#include <sys/ucontext.h>
using namespace std;

// KEPT FOR HISTORICAL PURPOSES
/*
 *
 * a^16 base*=base,  a^2
 * a^8 * a^8
 * a^4 * a^4 |
 * a^2 * a^2 |||
 * a^1
 *
 * a=a^2
 * a=a^2....

 */
int bigmod(int base, int exponent, int modulus) {
    int result = 1;
    base%=modulus;
    while(exponent) {
        if (exponent &1) result = (__int128)(result * base) % modulus;
        base = (__int128)base * base % modulus;
        exponent>>=1;
    }
    return result;
}

/*
 * 32s + 12t = gcd(32,12) = 4
 * 32,12
 * 12, 8; 32 = 2*12 + 8 = 2*(8*1 + 4 ) + 4*2 = 2*8 + 4*4
 * 2. 8, 4; 12 = 8*1 + 4
 * 1. 4, 0; 8 = 4*2 +0;
 * 0. 1, 0; 1 = 1*1 + 0
 *
 * gcd (4,0) = 4 = 4*1 + 0
 *       x   y
 * gcd (8,4)  =
 *
 *
 *
 * direct
 * 4 = 12 - 8*1
 *   = 12 - (32-2*32) = 12*3 - 1*32
 *
 * back
 *
 *
 *
 * back subsitute to get the above form
 *
 * gcd(118,25) = 1
 * 118 = 4*25 + 18
 * 25 = 1*18 + 7
 * 18 = 2*7 + 4
 * 7 = 1*4 + 3
 * 4 = 1*3 + 1 ; a=4,b=3; a comes from this eqn and b comes from the later
 *             ;
 * 3 = 3*1 + 0
 * 1 = 1*1 +0
 *
 * gcd(118,25)=gcd(1,0) =1 = 1*1 + 0; x=1, y=0
 * now moving the the previous line
 * gcd (1,0) =  gcd (3,1) = 3*1 + 0 should be now, in calc
 * gcd (4,3) = 4 + 3
 *
 *
 *
 *
 *
 */

int extended_gcd(int a, int b, int &x, int &y) {
    if (b==0) return x=1,y=0,a; // x,y comes from the previousline gcd(gcd,0) = gcd*1+0 equivalent to ax+by=gcd(a,b)
    int x1,y1;
    extended_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1 - a/b*y1 ;
}

int modinv(int a, int m) {
    int x,y;
    extended_gcd(a, m, x, y);
    if (x<0) x+=m;
    return x%m;
}



int main() {
    cout << "Hello, Al-Jamal!" << endl;
    int prime = 29;
    cout << "The prime number is: " << prime << endl;
    int generator = 2;
    cout << "The generator is: " << generator << endl;
    int secret = 15;
    cout << "The secret number is: " << secret << endl;


    return 0;
}
