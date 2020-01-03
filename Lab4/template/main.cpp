#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int len_temp, len_a;
string temp, a;
vector<bool> f;
vector<vector<bool> > dp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> temp >> a;
  len_temp = (int) temp.size(), len_a = (int) a.size();
  temp = "/" + temp;
  a = "/" + a;
  dp.resize(len_a + 1, vector<bool>(len_temp + 1, false));
  f.resize(len_temp + 1, false);
  f[0] = true;
  dp[0][0] = true;
  for (int i = 0; i <= len_a; i++) {
    for (int j = 1; j <= len_temp; j++) {
      if (temp[j] == '*' && f[j - 1]) {
        dp[i][j] = true;
        f[j] = true;
      }
      if ((temp[j] == '?' || temp[j] == a[i]) && i != 0) {
        dp[i][j] = dp[i - 1][j - 1];
        if (dp[i][j]) {
          f[j] = true;
        }
      }
    }
  }
  cout << (dp[len_a][len_temp] ? "YES" : "NO");
  return 0;
}
