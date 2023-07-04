#include <bits/stdc++.h>

using namespace std;

vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r)
            z[i] = min(r-i, z[i-l]);

        while (s[z[i]] == s[i + z[i]])
            z[i]++;
        
        if (z[i] + i > r) {
            r = z[i] + i;
            l = i;
        }
    }

    return z;
}