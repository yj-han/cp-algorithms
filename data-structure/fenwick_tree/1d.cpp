#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <numeric>
#include <cstring>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<int, int> mii;
typedef map<char, int> mci;
 
#define mp make_pair 
#define pb push_back
#define all(v) v.begin(), v.end()
 
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct FenwickTree {
    vi bit;
    int n;
    
    FenwickTree(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTree(vi a): FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int idx) {
        int ret = 0;
        for (idx++; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int delta) {
        for (idx++; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }
};


int sum(vector<int> &bit, int idx) {
	int ret = 0;
	for (idx++; idx > 0; idx -= idx & -idx)
		ret += bit[idx];
	return ret;
}

int sum(vector<int> &bit, int l, int r) {
	return sum(bit, r) - sum(bit, l-1);
}

void add(vector<int> &bit, int idx, int delta) {
	int n = bit.size();
	for (idx++; idx < n; idx += idx & -idx)
		bit[idx] += delta;
}
