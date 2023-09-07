#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 100;

vector<int> adj[maxn];  // adjacency list
bool is_removed[maxn];
int subtree_size[maxn];

int dfs(int u, int parent = 0) {
	subtree_size[u] = 1;
	for (int v : adj[u]) {
		if (v != parent && !is_removed[v]) { subtree_size[u] += dfs(v, u); }
	}

	return subtree_size[u];
}

/*
 * This function returns a centroid (a tree may have
 * two centroids) of the subtree containing node u
 * after node removals
 * @param u current node
 * @param sz size of current subtree after node removals
 * @param parent parent of u
 * @return first centroid found
 */
int get_centroid(int u, int sz, int parent = 0) {
	for (int v : adj[u]) {
		if (v != parent && !is_removed[v]) {
			if (subtree_size[v] * 2 > sz) { return get_centroid(v, sz, u); }
		}
	}
	return u;
}

void solve(int root = 1) {
	int c = get_centroid(root, dfs(root));

	// do something

	is_removed[c] = true;  // remove current centroid
	// solve subtrees
	for (int v : adj[c]) {
		if (!is_removed[v]) { solve(v); }
	}
}