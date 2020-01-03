#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int len_a, len_b;
string a, b;
vector<vector<int> > dp;

int main() {
  freopen("levenshtein.in", "r", stdin);
  freopen("levenshtein.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> a >> b;
  len_a = (int) a.size(), len_b = (int) b.size();
  a = "*" + a, b = "/" + b;
  dp.resize(len_a + 1, vector<int>(len_b + 1));
  dp[0][0] = 0;
  for (int i = 1; i <= len_a; i++) {
    dp[i][0] = i;
  }
  for (int j = 1; j <= len_b; j++) {
    dp[0][j] = j;
  }
  for (int i = 1; i <= len_a; i++) {
    for (int j = 1; j <= len_b; j++) {
      if (a[i] == b[j]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
      }
    }
  }
  cout << dp[len_a][len_b];
  return 0;
}
