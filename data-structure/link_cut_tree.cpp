#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// reference: https://justicehui.github.io/
struct Node {
    Node* l;
    Node* r;
    Node* p;
    int sz;
    ll v, sum;
    bool flip;

    Node() : Node(0) {}
    Node(ll v) : v(v), sum(v) {
        l = r = p = nullptr;
        sz = 1;
        flip = false;
    }

    bool IsRoot() const {
        return !p || (this != p->l && this != p->r);
    }

    bool IsLeft() const {
        return this == p->l;
    }

    void Rotate() {
        if (IsLeft()) {
            if (r) {
                r->p = p;
            }
                p->l = r;
                r = p;
        } else {
            if (l) {
                l->p = p;
            }
            p->r = l;
            l = p;
        }

        if (!p->IsRoot()) {
            (p->IsLeft() ? p->p->l : p->p->l) = this;
        }
        auto t = p;
        p = t->p;
        t->p = this;
        t->Update();
        Update();
    }
    
    void Update() {
        sz = 1;
        sum = v;
        if (l) {
            sz += l->sz, sum += l->sum;
        }
        if (r) {
            sz += r->sz, sum += r->sum;
        }
    }

    void Update(ll val) {
        v = val;
        Update();
    }

    void Push() {

    }
};

void Splay(Node* x) {
    while (!x->IsRoot()) {
        if (!x->p->IsRoot()) {
            x->p->p->Push();
        }
        x->p->Push();
        x->Push();
        if (x->p->IsRoot()) {
            continue;
        }
        
        if (x->IsLeft() == x->p->IsLeft()) {
            x->p->Rotate();
        } else {
            x->Rotate();
        }
        x->Rotate();
    }
    x->Push();
}

void Access(Node* x) {
    Splay(x);
    x->r = nullptr;
    while (x->p) {
        Splay(x->p);
        x->p->r = x;
        Splay(x->p);
    }
}

void Link(Node* p, Node* c) {
    Access(c);
    Access(p);
    c->l = p;
    p->p = c;
}

void Cut(Node* x) {
    Access(x);
    x->l->p = nullptr;
    x->l = nullptr;
}

Node* GetRoot(Node* x) {
    Access(x);
    while (x->l) {
        x = x->l;
    }
    Splay(x);
    return x;
}

Node* GetParent(Node* x) {
    Access(x);
    if (!x->l) {
        return nullptr;
    }
    x = x->l;
    while (x->r) {
        x = x->r;
    }
    Splay(x);
    return x;
}

int GetDepth(Node* x) {
    Access(x);
    if (x->l) {
        return x->l->sz;
    }
    return 0;
}

Node* get_lca(Node* x, Node* y) {
    Access(x);
    Access(y);
    Splay(x);

    return x->p ? x->p : x;
}

ll vertex_query(Node* x, Node* y) {
    Node* l = get_lca(x, y);
    ll ret = l->v;
    Access(x);
    Splay(l);
    if (l->r) {
        ret = ret + l->r->sum;
    }
    Access(y);
    Splay(l);
    if (l->r) {
        ret = ret + l->r->sum;
    }
    return ret;
}

void Update(Node* x, ll val) {
    Splay(x);
    x->Update(val);
}