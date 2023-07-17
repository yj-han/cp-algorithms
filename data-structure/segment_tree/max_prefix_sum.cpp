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

struct node {
    ll sum, pref;
    node(ll sum, ll pref): sum(sum), pref(pref) {}
    node(ll x = 0): sum(x), pref(max(0LL, x)) {}
    friend node operator+(const node &a, const node &b) {
        return {a.sum + b.sum, max(a.pref, a.sum + b.pref)};
    }
};

void build(vector<node> &t, vll &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = node(a[tl]);
    } else {
        int tm = (tl + tr)/2;
        build(t, a, v*2, tl, tm);
        build(t, a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void update(vector<node> &t, int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = node(val);
    } else {
        int tm = (tl + tr)/2;
        (pos <= tm)?
            update(t, v*2, tl, tm, pos, val): 
            update(t, v*2+1, tm+1, tr, pos, val);
        t[v] = t[v*2] + t[v*2+1];
    }
}

node query(vector<node> &t, int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (tl == l && tr == r) 
        return t[v];
    int tm = (tl + tr)/2;
    return query(t, v*2, tl, tm, l, min(r, tm))
            + query(t, v*2+1, tm+1, tr, max(l, tm+1), r);
}
