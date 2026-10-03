#include <bits/stdc++.h>
#include <cassert>
using namespace std;


char _xor (char a,char b) {
    a-='0';
    b-='0';
    return '0' + (a ^ b);
}

string to_bin(char c) {
    string s= "";
    for (int i=7;i>=0;i--) {
        if (c & (1 << i)) s+="1";
        else s+="0";
    }
    return s;
}


string str_to_bin (string s) {
    string r="";
    for (int i=0;i<s.size();i++) {
        r+=to_bin(s[i]);
    }
    return r;
}

char to_char(string s) {
    char c  =0;
    for (int i=0;i<s.size();i++) {
        c+= (s[i]-'0') << (s.size()-i-1);
    }
    return c;
}
string bin_to_str(string s) {
    string res = "";
    for (int i=0;i<s.size();i+=8) {
        res+= to_char(s.substr(i,8));
    }
    return res;
}

string vernam (string s, string k) {
    assert(s.size() == k.size());
    s = str_to_bin(s);
    k = str_to_bin(k);
    string r="";
    for (int i=0;i<s.size();i++) {
        r+= _xor(s[i],k[i]);
    }
    return bin_to_str(r);
}


int main () {
    string  k= vernam("hi","go");
    cout<<str_to_bin(k)<<endl;
    cout<<vernam(k,"go")<<endl;
}
