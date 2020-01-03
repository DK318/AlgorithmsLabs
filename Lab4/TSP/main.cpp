#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int n, m;
vector<int> mask;
vector<vector<ll> > dp, weights;

int get_mask() {
  int res = 0;
  for (int i = 0; i < n; i++) {
    res += (mask[i] << (n - 1 - i));
  }
  return res;
}

void calc(int i, int bal) {
  if (i != n) {
    mask[i] = 0;
    calc(i + 1, bal);
    mask[i] = 1;
    calc(i + 1, bal - 1);
  } else {
    if (bal > 0) {
      return;
    }
    int num_mask = get_mask();
    for (int k = 0; k < n; k++) {
      if (mask[k] == 1) {
        dp[k][num_mask] = INF;
        int new_mask = (num_mask ^ (1 << (n - 1 - k)));
        for (int j = 0; j < n; j++) {
          if (mask[j] != 0 && weights[k][j] != -1 && k != j && dp[j][new_mask] != -1) {
            dp[k][num_mask] = min(dp[k][num_mask], dp[j][new_mask] + weights[k][j]);
          }
        }
        if (dp[k][num_mask] == INF) {
          dp[k][num_mask] = -1;
        }
      }
    }
  }
}

void add_edge(int u, int v, ll w) {
  weights[u][v] = w;
  weights[v][u] = w;
}

int main() {
  freopen("salesman.in", "r", stdin);
  freopen("salesman.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  if (n == 1) {
    cout << 0;
    return 0;
  }
  mask.resize(n, 0);
  weights.resize(n, vector<ll>(n, -1));
  dp.resize(n, vector<ll>((1 << n), INF));
  for (int i = 0; i < m; i++) {
    int u, v;
    int w;
    cin >> u >> v >> w;
    u--; v--;
    add_edge(u, v, w);
  }
  for (int i = 0; i < n; i++) {
    dp[i][1 << (n - i - 1)] = 0;
  }
  for (int i = 2; i <= n; i++) {
    calc(0, i);
  }
  ll ans = INF;
  for (int i = 0; i < n; i++) {
    if (dp[i][(1 << n) - 1] != -1) {
      ans = min(ans, dp[i][(1 << n) - 1]);
    }
  }
  if (ans == INF) {
    cout << -1;
  } else {
    cout << ans;
  }
  return 0;
}
