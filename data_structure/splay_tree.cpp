#include <bits/stdc++.h>
using namespace std;

// reference: https://justicehui.github.io/
struct Node {
    Node* l;
    Node* r;
    Node* p;
    int key, cnt;
};

Node* tree;

void Update(Node *x) {
    x->cnt = 1;
    if (x->l) {
        x->cnt += x->l->cnt;
    }
    if (x->r) {
        x->cnt += x->r->cnt;
    }
}

void Rotate(Node* x) {
    Node* p = x->p;
    Node* b = NULL;
    if (!p) {
        return;
    }

    if (x == p->l) {
        p->l = b = x->r;
        x->r = p;
    } else {
        p->r = b = x->l;
        x->l = p;
    }

    x->p = p->p;
    p->p = x;
    if (b) {
        b->p = p;
    }
    (x->p ? p == x->p->l ? x->p->l : x->p->r : tree) = x;
    Update(p);
    Update(x);
}

void Splay(Node* x) {
    while (x->p) {
        Node* p = x->p;
        Node* g = p->p;
        if (g) {
            if ((x == p->l) == (p == g->l)) {
                Rotate(p); // Zig-Zig
            } else {
                Rotate(x); // Zig-Zag
            }
            Rotate(x);
        }
    }
}

void Insert(int key) {
    Node* p = tree;
    Node** pp;

    if (!p) {
        Node* x = new Node;
        tree = x;
        x->l = x->r = x->p = NULL;
        x->key = key;
        return;
    }

    while (1) {
        if (key == p->key) {
            return;
        }
        if (key < p->key) {
            if (!p->l) {
                pp = &p->l;
                break;
            }
            p = p->l;
        } else {
            if (!p->r) {
                pp = &p->r;
                break;
            }
            p = p->r;
        }
    }

    Node* x = new Node;
    *pp = x;
    x->l = x->r = NULL;
    x->p = p, x->key = key;
    Splay(x);
}

bool Find(int key) {
    Node* p = tree;
    if (!p) {
        return false;
    }
    while (p) {
        if (key == p->key) {
            break;
        }
        if (key < p->key) {
            if (!p->l) {
                break; // fail
            }
            p = p->l;
        } else {
            if (!p->r) {
                break; // fail
            }
            p = p->r;
        }
    }

    Splay(p);
    return key == p->key;
}

void Delete(int key) {
    if (!Find(key)) {
        return;
    }

    Node* p = tree;
    if (p->l && p->r) {
        tree = p->l, tree->p = NULL;

        Node* x = tree;
        while (x->r) {
            x = x->r;
        }
        x->r = p->r;
        p->r->p = x;
        delete p;
        return;
    }
    if (p->l) {
        tree = p->l;
        tree->p = NULL;
        delete p; return;
    }
    if (p->r) {
        tree = p->r;
        tree->p = NULL;
        delete p;
        return;
    }

    delete p;
    tree = NULL;
}

void Kth(int k) {
    Node* x = tree;
    while (1) {
        while (x->l && x->l->cnt > k) {
            x = x->l;
        }
        if (x->l) {
            x -= x->l->cnt;
        }
        if (!k--) {
            break;
        }
        x = x->r;
    }
    Splay(x);
}