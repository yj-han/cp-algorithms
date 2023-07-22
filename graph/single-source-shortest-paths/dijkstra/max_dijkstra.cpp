#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
 
struct BFS {
    struct edge {
        int node = -1, type = -1;
 
        edge() {} 
        edge(int _node, int _type) : node(_node), type(_type) {}
    };
 
    int n;
    vector<vector<edge>> adj;
    vector<array<int, 2>> dist;
 
    BFS(int _n = 0) {
        init(_n);
    }
 
    void init(int _n) {
        n = _n;
        adj.assign(n, {});
    }
 
    void add_directional_edge(int a, int b, int type) {
        assert(0 <= type && type <= 1);
        adj[a].emplace_back(b, type);
    }
 
    void add_bidirectional_edge(int a, int b, int type) {
        assert(0 <= type && type <= 1);
        add_directional_edge(a, b, type);
        add_directional_edge(b, a, type);
    }
 
    int get_dist(int node) const {
        return max(dist[node][0], dist[node][1]);
    }
 
    void bfs_check(queue<int> &next_q, int node, int type, int new_dist) {
        if (new_dist < dist[node][type]) {
            dist[node][type] = new_dist;
 
            if (dist[node][type] >= dist[node][!type]) {
                next_q.push(node);
            }
        }
    }
 
    void bfs() {
        queue<int> q, next_q;
        dist.assign(n, {INF, INF});
        dist[n - 1][0] = dist[n - 1][1] = 0;
        q.push(n - 1);
        int level = 0;
 
        while (!q.empty() || !next_q.empty()) {
            while (!q.empty()) {
                int top = q.front(); q.pop();
                if (level > get_dist(top)) {
                    continue;
                }
                for (edge &e : adj[top]) {
                    bfs_check(next_q, e.node, e.type, get_dist(top) + 1);
                }
            }
            swap(q, next_q);
            level++;
        }
    }
};
