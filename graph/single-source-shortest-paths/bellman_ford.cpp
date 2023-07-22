#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m, v;
ll INF = 1e18;

void bellman_ford() {
    vector<tuple<int, int, ll>> edges;
    vector<ll> d(n, INF);
    vector<int> p(n, -1);
    d[v] = 0;
    int x;
    for (int i = 0; i < n; i++) {
        x = -1;

        for (auto [a, b, w] : edges) {
            if (d[a] < INF) {
                if (d[b] > d[a] + w) {
                    d[b] = max(-INF, d[a] + w);
                    p[b] = a;
                    x = b;
                }
            }
        }
    }

    if (x == -1) {
        cout << "No negative cycle from " << v;
    } else {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "Negative cycle: ";
        for (int u : path)
            cout << u << ' ';
    }
}