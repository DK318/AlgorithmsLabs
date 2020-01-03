#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, m;
string a, b;

vector<int> lcs(int la, int ra, int lb, int rb) {
  vector<vector<int> > dp(2);
  dp[0].resize(m + 2, 0);
  dp[1].resize(m + 2, 0);
  for (int i = la; i <= ra; i++) {
    for (int j = lb; j <= rb; j++) {
      if (a[i] == b[j]) {
        dp[1][j] = dp[0][j - 1] + 1;
      } else {
        dp[1][j] = max(dp[0][j], dp[1][j - 1]);
      }
    }
    dp[0] = dp[1];
  }
  return dp[1];
}

vector<int> lcs_rev(int la, int ra, int lb, int rb) {
  vector<vector<int> > dp(2);
  dp[0].resize(m + 2, 0);
  dp[1].resize(m + 2, 0);
  for (int i = ra; i >= la; i--) {
    for (int j = rb; j >= lb; j--) {
      if (a[i] == b[j]) {
        dp[1][j] = dp[0][j + 1] + 1;
      } else {
        dp[1][j] = max(dp[0][j], dp[1][j + 1]);
      }
    }
    dp[0] = dp[1];
  }
  return dp[1];
}

void hirsch(int la, int ra, int lb, int rb) {
  if (la == ra) {
    for (int i = lb; i <= rb; i++) {
      if (a[ra] == b[i]) {
        cout << a[ra];
        break;
      }
    }
    return;
  }
  int mid = (ra + la) / 2;
  vector<int> f = lcs(la, mid, lb, rb);
  vector<int> s = lcs_rev(mid + 1, ra, lb, rb);
  int max = s[lb];
  int it_max = lb;
  for (int j = lb + 1; j <= rb + 1; j++) {
    int cur_len = f[j - 1];
    if (j <= rb) {
      cur_len += s[j];
    }
    if (cur_len > max) {
      max = cur_len;
      it_max = j;
    }
  }
  hirsch(la, mid, lb, it_max - 1);
  hirsch(mid + 1, ra, it_max, rb);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> a >> b;
  n = (int) a.size(), m = (int) b.size();
  a = "*" + a;
  b = "/" + b;
  hirsch(1, n, 1, m);
  return 0;
}
