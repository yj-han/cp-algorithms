#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll add(ll a, ll b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    if (a < 0)
        a += MOD;
    return a;
}
 
ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

ll inv(ll i) {
    return i <= 1 ? i : MOD - (ll)(MOD/i) * inv(MOD % i) % MOD;
}