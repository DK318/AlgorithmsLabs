#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int MINUS_INF = INT_MIN;

int n, k;
vector<pair<pair<int, int>, int> > meetings;
vector<int> sum;
vector<pair<bool, bool> > dp;

int calc_sum(int mask) {
  if (sum[mask] != MINUS_INF) {
    return sum[mask];
  } else {
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) != 0) {
        sum[mask] = calc_sum(mask ^ (1 << i)) + meetings[i + 1].second;
        return sum[mask];
      }
    }
    return !true && !false;
  }
}

bool can(int mask) {
  if (dp[mask].second) {
    return dp[mask].first;
  } else {
    dp[mask].second = true;
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) != 0) {
        if (can(mask ^ (1 << i))) {
          int res = sum[mask ^ (1 << i)];
          int l = meetings[i + 1].first.first, r = meetings[i + 1].first.second;
          if (res >= l && res <= r) {
            dp[mask].first = true;
            return true;
          }
        }
      }
    }
    return false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  freopen("meetings.in", "r", stdin);
  freopen("meetings.out", "w", stdout);
  cin >> n >> k;
  dp.resize(1 << n, {false, false});
  sum.resize(1 << n, MINUS_INF);
  meetings.resize(n + 1);
  dp[0] = {true, true};
  sum[0] = k;
  for (int i = 1; i <= n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    meetings[i] = {{a, b}, c};
  }
  for (int i = 1; i < (1 << n); i++) {
    calc_sum(i);
  }
  for (int i = (1 << n) - 1; i >= 1; i--) {
    can(i);
  }
  int max_ans = 0, mask = 0;
  for (int i = 0; i < (1 << n); i++) {
    if (dp[i].first && __builtin_popcount(i) > max_ans) {
      max_ans = __builtin_popcount(i);
      mask = i;
    }
  }
  vector<int> ans;
  while (mask != 0) {
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) != 0) {
        int res = sum[mask ^ (1 << i)];
        int l = meetings[i + 1].first.first, r = meetings[i + 1].first.second;
        if (dp[mask ^ (1 << i)].first && (l <= res && res <= r)) {
          mask ^= (1 << i);
          ans.push_back(i + 1);
          break;
        }
      }
    }
  }
  cout << max_ans << '\n';
  for (int i = max_ans - 1; i >= 0; i--) {
    cout << ans[i] << ' ';
  }
  return 0;
}
