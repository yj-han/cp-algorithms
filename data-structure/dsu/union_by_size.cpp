#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;
 
typedef vector<int> vi;

#define all(v) v.begin(), v.end()

class DSU {
    private:
        int n;
        vi parent, sz;
    
    public:
        DSU(int n) {
            this->n = n;
            iota(all(parent), 0);
            sz.assign(n, 1);
        }

        int find_set(int u) {
            if (parent[u] == u)
                return u;
            return parent[u] = find_set(parent[u]);
        }

        void union_sets_by_sz(int u, int v) {
            u = find_set(u);
            v = find_set(v);

            if (u != v) {
                if (sz[u] < sz[v]) 
                    swap(u, v);
                sz[u] += sz[v];
                parent[v] = u;
            }
        }

        bool is_same(int u, int v) {
            return find_set(u) == find_set(v);
        }
};
