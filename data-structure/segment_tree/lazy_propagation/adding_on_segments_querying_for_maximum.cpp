#include <iostream>
#include <vector>

using namespace std;
 

void build(vector<long long> &t, vector<long long> &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr)/2;
        build(t, a, v*2, tl, tm);
        build(t, a, v*2+1, tm+1, tr);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

void push(vector<long long> &t, vector<long long> &lazy, int v) {
    t[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(vector<long long> &t, vector<long long> &lazy, int v, int tl, int tr, int l, int r, int addend) {
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

long long query(vector<long long> &t, vector<long long> &lazy, int v, int tl, int tr, int l, int r) {
    if (l > r) return;
    if (tl == l && tr == r)
        return t[v];
    push(t, lazy, v);
    int tm = (tl + tr)/2;
    return max(query(t, lazy, v*2, tl, tm, l, min(r, tm)),
                query(t, lazy, v*2+1, tm+1, tr, max(l, tm+1), tr));
}
