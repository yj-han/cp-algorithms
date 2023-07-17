#include <bits/stdc++.h>
using namespace std;

struct node {
    long long sum, left_max, right_max, cur_max;
    node(long long sum, long long left_max, long long right_max, long long cur_max): 
        sum(sum), left_max(left_max), right_max(right_max), cur_max(cur_max) {}
    node(long long x = 0): sum(x), left_max(max(0ll, x)), right_max(max(0ll, x)), cur_max(max(0ll, x)) {}
    friend node operator+(const node &a, const node &b) {
        long long sum = a.sum + b.sum;
        long long left_max = max(a.left_max, a.sum + b.left_max);
        long long right_max = max(b.right_max, a.right_max + b.sum);
        long long cur_max = max({left_max, right_max, a.cur_max, b.cur_max, sum, a.right_max + b.left_max});
        return {sum, left_max, right_max, cur_max};
    }
};

void build(vector<node> &t, vector<long long> &a, int v, int tl, int tr) {
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
