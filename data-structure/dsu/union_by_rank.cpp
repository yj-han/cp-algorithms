#include <bits/stdc++.h>

using namespace std;
 
class DSU {
    private:
        int n;
        vector<int> parent, rank;
    
    public:
        DSU(int n) {
            this->n = n;
            iota(parent.begin(), parent.end(), 0);
            rank.assign(n, 0);
        }

        int find_set(int u) {
            if (parent[u] == u)
                return u;
            return parent[u] = find_set(parent[u]);
        }

        void union_set(int u, int v) {
            u = find_set(u);
            v = find_set(v);

            if (u != v) {
                if (rank[u] < rank[v]) 
                    swap(u, v);
                parent[v] = u;
                if (rank[u] == rank[v])
                    rank[u]++;
            }
        }

        bool is_same(int u, int v) {
            return find_set(u) == find_set(v);
        }
};
