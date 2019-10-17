#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Cashier {
  ll a;
  ll b;
  ll t;

  Cashier(ll a, ll b, ll t) : a(a), b(b), t(t) {}
};

ll n, m, p;
vector<Cashier> cashiers;

void msort(vector<ll> &x) {
  if (x.size() < 2) {
    return;
  }
  vector<ll> b, c;
  int mid = x.size() / 2;
  for (int i = 0; i < mid; i++) {
    b.push_back(x[i]);
  }
  for (int i = mid; i < (int) x.size(); i++) {
    c.push_back(x[i]);
  }
  msort(b);
  msort(c);
  int i = 0, l = 0, r = 0;
  while (l < mid && r < (int) c.size()) {
    if (b[l] >= c[r]) {
      x[i++] = b[l++];
    } else {
      x[i++] = c[r++];
    }
  }
  while (l < mid) {
    x[i++] = b[l++];
  }
  while (r < (int) c.size()) {
    x[i++] = c[r++];
  }
}

ll binary() {
  ll l = -1, r = (ll) 1e11;
  while (l < r - 1) {
    ll mid = (l + r) / 2;
    vector<ll> ans((int) m);
    for (int i = 0; i < m; i++) {
      ans[i] = max(0ll, (mid - cashiers[i].b - cashiers[i].t) / cashiers[i].a);
    }
    msort(ans);
    ll sum = 0;
    for (int i = 0; i < min(n, m); i++) {
      sum += ans[i];
    }
    if (sum >= p) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> m;
  ll ans = (ll) 1e18;
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    ll a, b, t;
    cin >> a >> b >> t;
    if (a == 0) {
      ans = min(ans, b + t);
      cnt++;
    } else {
      cashiers.push_back(Cashier(a, b, t));
    }
  }
  m -= cnt;
  cin >> n >> p;
  if (p == 0) {
    cout << 0;
    return 0;
  }
  if (m == 0) {
    cout << ans;
  } else {
    cout << min(ans, binary());
  }
  return 0;
}
