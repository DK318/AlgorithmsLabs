#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

const ll MOD = 999999937;

vector<vector<ll> > matrix {{1, 1, 1, 1, 1},
                             {1, 1, 1, 1, 1},
                             {1, 1, 1, 1, 1},
                             {1, 1, 0, 1, 0},
                             {1, 1, 0, 1, 0}};

vector<vector<ll> > e {{1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 0, 0, 0, 1}};

vector<vector<ll> > mult(vector<vector<ll> > m1, vector<vector<ll> > m2) {
  vector<vector<ll> > res(5);
  for (int i = 0; i < 5; i++) {
    res[i].resize(5);
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ll c = 0;
      for (int k = 0; k < 5; k++) {
        c += (m1[i][k] * m2[k][j]) % MOD;
        c %= MOD;
      }
      res[i][j] = c;
    }
  }
  return res;
}

vector<vector<ll> > binpow(vector<vector<ll> > m, ll k) {
  if (k == 0) {
    return e;
  }
  if (k % 2) {
    return mult(binpow(m, k - 1), m);
  } else {
    vector<vector<ll> > m1 = binpow(m, k / 2);
    return mult(m1, m1);
  }
}

int main() {
  freopen("sequences.in", "r", stdin);
  freopen("sequences.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  ll t;
  while (true) {
    cin >> t;
    if (t == 0) {
      return 0;
    }
    if (t == 1) {
      cout << 5 << '\n';
      continue;
    }
    vector<vector<ll> > m = binpow(matrix, t - 1);
    ll ans = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        ans = (ans + m[i][j]) % MOD;
      }
    }
    cout << ans << '\n';
  }
}
