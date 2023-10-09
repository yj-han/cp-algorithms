#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

void build(vector<ll> &t, vector<ll> &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
        return;
    }

    int tm = (tl + tr)/2;
    build(t, a, v*2, tl, tm);
    build(t, a, v*2+1, tm+1, tr);
    t[v] = t[v*2] + t[v*2+1];
}

void push(vector<ll> &t, vector<ll> &lazy, int v, int tl, int tr) {
    t[v] += (tr-tl+1) * lazy[v];
    if (tl != tr) {
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
    }
    lazy[v] = 0;
}

void update(vector<ll> &t, vector<ll> &lazy, int v, int tl, int tr, int l, int r, ll d) {
    push(t, lazy, v, tl, tr);
    if (r < l) {
        return;
    }

    if (tl == l && tr == r) {
        lazy[v] += d;
        push(t, lazy, v, tl, tr);
    } else {
        int tm = (tl + tr)/2;
        update(t, lazy, v*2, tl, tm, l, min(r, tm), d);
        update(t, lazy, v*2+1, tm+1, tr, max(l, tm+1), r, d);
        t[v] = t[v*2] + t[v*2+1];
    }
}

ll query(vector<ll> &t, vector<ll> &lazy, int v, int tl, int tr, int l, int r) {
    push(t, lazy, v, tl, tr);
    if (r < l) {
        return 0;
    }
    
    if (tl == l && tr == r) {
        return t[v];
    }

    int tm = (tl + tr)/2;
    return query(t, lazy, v*2, tl, tm, l, min(r, tm))
            + query(t, lazy, v*2+1, tm+1, tr, max(l, tm+1), r);
}