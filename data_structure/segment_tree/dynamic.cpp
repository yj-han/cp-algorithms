#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node{
    Node *l, *r;
    ll v;
    Node(){ l = r = NULL; v = 0; }
} *root;

void update(Node *node, int s, int e, int x, int v){
    if (s == e) {
        node->v = v; return;
    }
    int m = s + e >> 1;
    if(x <= m){
        if (!node->l) node->l = new Node();
        update(node->l, s, m, x, v);
    } else {
        if(!node->r) node->r = new Node();
        update(node->r, m+1, e, x, v);
    }
    ll t1 = node->l ? node->l->v : 0;
    ll t2 = node->r ? node->r->v : 0;
    node->v = t1 + t2;
}
ll query(Node *node, int s, int e, int l, int r){
    if (!node) return 0;
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return node->v;
    int m = s + e >> 1;
    return query(node->l, s, m, l, r) + query(node->r, m+1, e, l, r);
}