#include <bits/stdc++.h>

using namespace std;


void dfs1(vector<vector<int>> &adj, vector<bool> &used, vector<int> &order, int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(adj, used, order, u);

    order.push_back(v);
}

void dfs2(vector<vector<int>> &adj_rev, vector<bool> &used, vector<int> &component, int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(adj_rev, used, component, u);
}

void scc() {
    int n;

    vector<vector<int>> adj(n), adj_rev(n);
    vector<bool> used(n, false);
    vector<int> order, component;
    
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs1(adj, used, order, i);
    }

    used.assign(n, false);
    reverse(order.begin(), order.end());
    for (auto v : order) {
        if (!used[v]) {
            dfs2 (adj_rev, used, component, v);
            component.clear();
        }
    }
}