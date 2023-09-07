#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> euler_path(vector<vector<pair<int, int>>> &adj, vector<bool> &used) {
    int n = adj.size();
    vector<pair<int, int>>::iterator its[n];

    int src = 0;
    for (int i = 0; i < n; i++) {
        its[i] = begin(adj[i]);
    }
    vector<pair<pair<int, int>, int>> ret, s = {{{src, -1}, -1}};
    while (!s.empty()) {
        int x = s.back().first.first;
        auto &it = its[x], en = end(adj[x]);
        while (it != en && used[it->second]) {
            it++;
        }
        if (it == en) {
            if (ret.size() && ret.back().first.second != x) {
                return {};
            }
            ret.push_back(s.back()), s.pop_back();
        }  else {
            s.push_back({{it->first, x}, it->second});
            used[it->second] = 1;
        }
    }

    if (ret.size() != used.size()+1) {
        return {};
    }
    
    vector<pair<int, int>> ans;
    for (auto t : ret) {
        ans.push_back({t.first.first, t.second});
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
