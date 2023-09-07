#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int fib_linear(int n) {
    int a = 0;
    int b = 1;
    for (int i = 0; i < n; i++) {
        int tmp = a + b;
        a = b;
        b = tmp;
    }
    return a;
}

struct matrix {
    long long mat[2][2];
    matrix friend operator *(const matrix &a, const matrix &b){
        matrix c;
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 2; j++) {
              c.mat[i][j] = 0;
              for (int k = 0; k < 2; k++) {
                  c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
              }
          }
        }
        return c;
    }
};

matrix matpow(matrix base, long long n) {
    matrix ans{ {
        {1, 0},
        {0, 1}
    } };
    while (n) {
        if(n&1)
            ans = ans*base;
        base = base*base;
        n >>= 1;
    }
    return ans;
}

// long long fib(int n) {
//     matrix base{ {
//         {1, 1},
//         {1, 0}
//     } };
//     return matpow(base, n).mat[0][1];
// }

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

ll sub(ll a, ll b) {
    return a - b < 0 ? MOD + a - b : a - b;
}

pair<ll, ll> fib(ll n) {
    if (n == 0)
        return make_pair(0, 1);

    auto p = fib(n >> 1);
    // f_{2k} = f_{k} * (2 * f_{k+1} - f_{k});
    ll c = mul(p.first, sub(mul(2, p.second), p.first));
    // f_{2k+1} = f_{k} * f_{k} + f_{k+1} * f_{k+1};
    ll d = add(mul(p.first, p.first), mul(p.second, p.second));
    return n & 1 ? make_pair(d, add(c, d)) : make_pair(c, d);
}
