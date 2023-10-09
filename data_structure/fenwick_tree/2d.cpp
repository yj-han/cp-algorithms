#include <bits/stdc++.h>>
using namespace std;
 
struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;
    
    FenwickTree2D(int n, int m) {
        this->n = n + 1;
        this->m = m + 1;
        bit.assign(n+1, vector<int>(m+1, 0));
    }

    FenwickTree2D(vector<vector<int>> a): FenwickTree2D(a.size(), a[0].size()) {
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < a[0].size(); j++)
                add(i, j, a[i][j]);
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x+1; i > 0; i -= i & -i)
            for (int j = y+1; j > 0; j -= j & -j)
                ret += bit[i][j];

        return ret;
    }

    int sum(int x1, int y1, int x2, int y2) {
        int s1 = sum(x2, y2);
        int s2 = sum(x2, y1-1);
        int s3 = sum(x1-1, y2);
        int s4 = sum(x1-1, y1-1);

        return s1-s2-s3+s4;
    }

    void add(int x, int y, int delta) {
        for (int i = x+1; i < n; i += i & -i)
            for (int j = y+1; j < m; j += j & -j)
                bit[i][j] += delta;
    }
};
