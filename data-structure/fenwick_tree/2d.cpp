#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <numeric>
#include <cstring>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<int, int> mii;
typedef map<char, int> mci;
 
#define mp make_pair 
#define pb push_back
#define all(v) v.begin(), v.end()
 
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct FenwickTree2D {
    vector<vi> bit;
    int n, m;
    
    FenwickTree2D(int n, int m) {
        this->n = n + 1;
        this->m = m + 1;
        bit.assign(n+1, vi(m+1, 0));
    }

    FenwickTree2D(vector<vi> a): FenwickTree2D(a.size(), a[0].size()) {
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
