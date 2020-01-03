#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

const int MOD = 1e9;

int n;
vector<ll> a, dp1, dp2;

void calc1() {
  ll l = 0, r = -1;
  for (ll i = 0; i < (ll) n; i++) {
    ll k = (i > r ? 0 : min(dp1[l + r - i], r - i));
    while (i + k < n && i - k >= 0 && a[i + k + 1] == a[i - k - 1]) {
      k++;
    }
    dp1[i] = k;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
}

void calc2() {
  ll l = 0, r = -1;
  for (ll i = 0; i < (ll) n; i++) {
    ll k = (i > r ? 0 : min(dp2[l + r - i + 1], r - i + 1));
    while (i + k - 1 < n && i - k >= 0 && a[i + k] == a[i - k - 1]) {
      k++;
    }
    dp2[i] = k;
    if (i + k - 1 > r) {
      l = i - k;
      r = i + k - 1;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  a.resize(n);
  dp1.resize(n);
  dp2.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  calc1();
  calc2();
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += dp1[i];
    ans %= MOD;
    ans += dp2[i];
    ans %= MOD;
  }
  cout << ans;
  return 0;
}
