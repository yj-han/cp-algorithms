#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

const int MOD = 1e9 + 7;
const int N = 2e5 + 100;

vector<ll> factorial(N, 1);

ll inv(ll i) {
    return i <= 1 ? i : MOD - (ll)(MOD/i) * inv(MOD % i) % MOD;
}

ll C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return factorial[n] * inv(factorial[k]) % MOD * inv(factorial[n - k]) % MOD;
}

void calc() {
    for (int i = 1; i < N; i++)
        factorial[i] = factorial[i-1] * (ll)i % MOD;
}