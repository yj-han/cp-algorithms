#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> parent;
vector<int> ranks;
vector<bool> bipartite;

void make_set(int v) {
    parent[v] = make_pair(v, 0);
    ranks[v] = 0;
    bipartite[v] = true;
}

pair<int, int> find_set(int v) {
    if (v != parent[v].first) {
        int parity = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second ^= parity;
    }
    return parent[v];
}

void add_edge(int a, int b) {
    pair<int, int> pa = find_set(a);
    a = pa.first;
    int x = pa.second;

    pair<int, int> pb = find_set(b);
    b = pb.first;
    int y = pb.second;

    if (a == b) {
        if (x == y)
            bipartite[a] = false;
    } else {
        if (ranks[a] < ranks[b])
            swap (a, b);
        parent[b] = make_pair(a, x^y^1);
        bipartite[a] = bipartite[a] & bipartite[b];
        if (ranks[a] == ranks[b])
            ++ranks[a];
    }
}

bool is_bipartite(int v) {
    return bipartite[find_set(v).first];
}
