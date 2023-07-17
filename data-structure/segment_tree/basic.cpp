#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


void build(vector<ll> &t, vector<int> &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr)/2;
        build(t, a, v*2, tl, tm);
        build(t, a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void update(vector<ll> &t, int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = ll(val);
    } else {
        int tm = (tl + tr)/2;
        (pos <= tm)?
            update(t, v*2, tl, tm, pos, val): 
            update(t, v*2+1, tm+1, tr, pos, val);
        t[v] = t[v*2] + t[v*2+1];
    }
}

ll query(vector<ll> &t, int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (tl == l && tr == r) 
        return t[v];
    int tm = (tl + tr)/2;
    return query(t, v*2, tl, tm, l, min(r, tm))
            + query(t, v*2+1, tm+1, tr, max(l, tm+1), r);
}
