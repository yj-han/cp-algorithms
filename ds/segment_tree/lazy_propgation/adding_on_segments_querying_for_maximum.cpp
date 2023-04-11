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

void push(vll &t, vll &lazy, int v) {
    t[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(vll &t, vll &lazy, int v, int tl, int tr, int l, int r, int addend) {
    if (l > r) return;
    if (tl == l && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(t, lazy, v);
        int tm = (tl + tr)/2;
        update(t, lazy, v*2, tl, tm, l, min(r, tm), addend);
        update(t, lazy, v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

ll query(vll &t, vll &lazy, int v, int tl, int tr, int l, int r) {
    if (l > r) return;
    if (tl == l && tr == r)
        return t[v];
    push(t, lazy, v);
    int tm = (tl + tr)/2;
    return max(query(t, lazy, v*2, tl, tm, l, min(r, tm)),
                query(t, lazy, v*2+1, tm+1, tr, max(l, tm+1), tr));
}
