#include <bits/stdc++.h>
using namespace std;

char encrypt(char c, int k) {
    switch (c) {
        case 'a' ... 'z':
            return 'a' + (c-'a' + k)%26;
        case 'A' ... 'Z':
            return 'A' + (c-'A' + k)%26;
        case '0' ... '9':
            return '0' + (c-'0' + k)%10;
    }
    return c;
}

char decrypt (char c, int k) {
    switch (c) {
        case 'a' ... 'z':
            return 'a' + (26+(c-'a' - k))%26;
        case 'A' ... 'Z':
            return 'A' + (26+(c-'A' - k))%26;
        case '0' ... '9':
            return '0' + (10+(c-'0' - k))%10;
    }
    return c;
}


int main () {
    string s =  "abc123";
    string e = "";
    int k =  1;
    for (int i =0 ;i< s.size(); i++) {
        e+= encrypt(s[i], k);
        cout<<e[i];
    }
    cout<<endl;
    for (int i =0 ;i< e.size(); i++) {
        cout<<decrypt(e[i], k);
    }
    cout<<endl;
}
