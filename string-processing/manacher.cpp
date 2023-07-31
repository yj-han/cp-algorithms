#include <bits/stdc++.h>
using namespace std;
 
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    int n = s.size();
    vector<vector<int>> p(2, vector<int>(n,0));
    for(int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0) {
        for(int i = 0; i < n; i++) {
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
}