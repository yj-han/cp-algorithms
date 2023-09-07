#include <bits/stdc++.h>
using namespace std;
 
vector<vector<int>> manacher(string s) {
    int n = s.size();
    vector<vector<int>> p(2, vector<int>(n,0));
    for (int z = 0; z < 2; z++) {
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            if (i < r) {
                p[z][i] = min(r-i+!z, p[z][l+r-i+!z]);
            }
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L-1 >= 0 && R+1 < n && s[L-1] == s[R+1]) {
                p[z][i]++, L--, R++;
            }
            if (R > r) {
                l = L, r = R;
            }
        }
    }
    return p;
}

string str;
vector<int> rad;
int ans = 0;
string out;

void manacher(string &s) {
    rad = vector<int> ((int)str.length(), 0);
    int mr = 0, mid;
    for (int i = 1; i < str.length(); ++i) {
        rad[i] = i < mr ? min(mr - i, rad[mid * 2 - i]) : 1;
        for (; str[i + rad[i]] == str[i - rad[i]]; ++rad[i]) 
            if (i + rad[i] > mr) 
                mid = i, mr = i + rad[i];
        if (rad[i] - 1 > ans) {
            ans = rad[i] - 1; 
            out = s.substr((i - ans) / 2, ans); 
        }
    }
}

void init(string &s) {
    str = string((int)s.length() * 2 + 2, ' ');
    str[0] = str[1] = '#';
    for (int i = 0; i < s.length(); ++i) {
        str[i * 2 + 2] = s[i];
        str[i * 2 + 3] = '#';
    }
}

string longestPalindrome(string &s) {
    init(s);

}
