#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> parent, ranks;

void make_set(int v) {
    parent[v] = v;
    ranks[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (ranks[a] < ranks[b])
            swap(a, b);
        parent[b] = a;
        if (ranks[a] == ranks[b])
            ranks[a]++;
    }
}

struct edge {
    int u, v;
    ll weight;
    bool operator<(edge const& other) {
        return weight < other.weight;
    }
};

vector<edge> kruskal(int n, vector<edge> &edges) {
    ll cost = 0;
    vector<edge> result;
    parent.resize(n);
    ranks.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i);

    sort(edges.begin(), edges.end());

    for (edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v);
        }
    }
    return result;
}
