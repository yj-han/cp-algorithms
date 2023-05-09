#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;

int dfs_timer = 0;

void dfs(vector<vi> &adj, vi &time_in, vi &time_out, vi &color, int v) {
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
        if (color[u] == 0)
            dfs(adj, time_in, time_out, color, u);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}