#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct FenwickTree {
    vector<ll> bit;
    int n;
    
    FenwickTree(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }
 
    FenwickTree(vector<ll> a): FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
 
    ll query(int idx) {
        ll ret = 0;
        for (idx++; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
 
    void add(int idx, ll delta) {
        for (idx++; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }
};


int sum(vector<int> &bit, int idx) {
    int ret = 0;
    for (idx++; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}

int sum(vector<int> &bit, int l, int r) {
    return sum(bit, r) - sum(bit, l-1);
}

void add(vector<int> &bit, int idx, int delta) {
    int n = bit.size();
    for (idx++; idx < n; idx += idx & -idx)
        bit[idx] += delta;
}
