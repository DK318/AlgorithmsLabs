#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

vector<vector<int> > dp;
vector<int> ans, m, c;

void get_ans(int n, int w) {
  if (dp[n][w] == 0) {
    return;
  }
  if (dp[n - 1][w] == dp[n][w]) {
    get_ans(n - 1, w);
  } else {
    get_ans(n - 1, w - m[n]);
    ans.push_back(n);
  }
}

int main() {
  freopen("knapsack.in", "r", stdin);
  freopen("knapsack.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n, w; cin >> n >> w;
  m.resize(n + 1);
  c.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> m[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  dp.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    dp[i].resize(w + 1);
  }
  for (int i = 0; i <= n; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= w; i++) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= w; j++) {
      if (j >= m[i]) {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - m[i]] + c[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  int max_c = INT_MIN, cur_w = -1;
  for (int i = 0; i <= w; i++) {
    max_c = max(max_c, dp[n][i]);
    cur_w = i;
  }
  get_ans(n, cur_w);
  cout << ans.size() << '\n';
  for (int i = 0; i < (int) ans.size(); i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}
