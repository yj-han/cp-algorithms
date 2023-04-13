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

void build(vll &t, vll &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr)/2;
        build(t, a, v*2, tl, tm);
        build(t, a, v*2+1, tm+1, tr);
    }
}

void push(vi &t, vb &marked, int v) {
    if (marked[v]) {
        t[v*2] = t[v*2+1] = t[v];
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}

void update(vi &t, vb &marked, int v, int tl, int tr, int l, int r, int val) {
    if (l > r) return;
    if (l == tl && r == tr) {
        t[v] = val;
        marked[v] = true;
    } else {
        push(t, marked, v); // push the last update
        int tm = (tl + tr)/2;
        update(t, marked, v*2, tl, tm, l, min(r, tm), val);
        update(t, marked, v*2+1, tm+1, tr, max(l, tm+1), r, val);
    }
}

int query(vi &t, vb &marked, int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    push(t, marked, v);
    int tm = (tl + tr)/2;
    return (pos <= tm)? query(t, marked, v, tl, tm, pos): query(t, marked, v, tl, tm, pos);
}
