#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

int n;
vector<pair<ll, ll> > a;
vector<vector<ll> > dp;
vector<vector<string> > ans;

int main() {
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    a[i] = {x, y};
  }
  dp.resize(n, vector<ll>(n, INT_MAX));
  ans.resize(n, vector<string>(n));
  for (int i = 0; i < n; i++) {
    dp[i][i] = 0;
    ans[i][i] = "A";
  }
  for (int l = 1; l < n; l++) {
    for (int i = 0; i < n - l; i++) {
      int j = i + l;
      for (int k = i; k < j; k++) {
        ll cur = dp[i][k] + dp[k + 1][j] + a[i].first * a[k].second * a[j].second;
        if (cur < dp[i][j]) {
          dp[i][j] = cur;
          ans[i][j] = "(" + ans[i][k] + ans[k + 1][j] + ")";
        }
      }
    }
  }
  cout << ans[0][n - 1];
  return 0;
}
