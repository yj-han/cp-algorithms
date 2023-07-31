#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct edge {
    int to, w;

    bool operator<(edge const &other) {
        return w < other.w;
    }
};

void dijkstra_densed(int s, vector<vector<edge>> &adj, vector<int> &d, vector<int> &p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> used(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        // find the closest vertex
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (d[v] == INF)
            break;
        
        used[v] = true;
        for (auto e : adj[v]) {
            if (d[v] + e.w < d[e.to]) {
                d[e.to] = d[v] + e.w;
                p[e.to] = v;
            }
        }
    }
}

void dijkstra_sparsed(int s, vector<vector<edge>> &adj, vector<int> &d, vector<int> &p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        int d_v = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (d_v != d[v]) continue;

        for (auto e : adj[v]) {
            if (d[v] + e.w < d[e.to]) {
                d[e.to] = d[v] + e.w;
                p[e.to] = v;
                pq.push({d[e.to], e.to});
            }
        }
    }
}