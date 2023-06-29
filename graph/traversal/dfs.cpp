#include <bits/stdc++.h>

using namespace std;

int dfs_timer = 0;

void dfs(vector<vector<int>> &adj, vector<int> &time_in, vector<int> &time_out, vector<int> &color, int v) {
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
        if (color[u] == 0)
            dfs(adj, time_in, time_out, color, u);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}