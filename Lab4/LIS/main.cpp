#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int INF = INT_MAX;
const int MININF = INT_MIN;

int n, len = 0;
vector<int> a, dp, pos, prv, ans;

int main() {
  freopen("lis.in", "r", stdin);
  freopen("lis.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  dp.resize(n + 1, INF);
  dp[0] = MININF;
  pos.resize(n + 1);
  pos[0] = -1;
  prv.resize(n);
  for (int i = 0; i < n; i++) {
    int j = (int) (upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
    if (dp[j - 1] < a[i] && a[i] < dp[j]) {
      dp[j] = a[i];
      pos[j] = i;
      prv[i] = pos[j - 1];
      len = max(len, j);
    }
  }
  for (int p = pos[len]; p != -1; p = prv[p]) {
    ans.push_back(a[p]);
  }
  cout << ans.size() << '\n';
  for (int i = (int) ans.size() - 1; i >= 0; i--) {
    cout << ans[i] << ' ';
  }
  return 0;
}
