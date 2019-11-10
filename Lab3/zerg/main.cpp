#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

const ll p = 1e6 + 3;

int n, m;
ll zerg = 0;
vector<pair<ll, ll> > dsu;
vector<ll> sz, read;

void init() {
  dsu.resize(n);
  sz.resize(n);
  read.resize(n, 0);
  for (int i = 0; i < n; i++) {
    dsu[i] = {i, 0};
    sz[i] = 1;
  }
}

ll find(ll x) {
  if (x == dsu[(int) x].first) {
    return x;
  }
  ll v = find(dsu[(int) x].first);
  dsu[(int) x].second += dsu[(int) dsu[(int) x].first].second;
  if (v == dsu[(int) x].first) {
    dsu[(int) x].second -= dsu[(int) v].second;
  }
  dsu[(int) x].first = v;
  return v;
}

void unite(ll x, ll y) {
  x = find(x); y = find(y);
  if (x == y) {
    return;
  }
  zerg = (13 * zerg + 11) % p;
  if (sz[(int) x] < sz[(int) y]) {
    swap(x, y);
  }
  dsu[(int) y].second -= dsu[(int) x].second;
  dsu[(int) y].first = x;
  sz[(int) x] += sz[(int) y];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  init();
  for (int i = 0; i < m; i++) {
    int type; cin >> type;
    if (type == 1) {
      ll x; cin >> x;
      x = (x + zerg) % n;
      x = find(x);
      dsu[(int) x].second++;
      zerg = (30 * zerg + 239) % p;
    } else if (type == 2) {
      ll x, y; cin >> x >> y;
      x = (x + zerg) % n;
      y = (y + zerg) % n;
      unite(x, y);
    } else {
      ll x; cin >> x;
      x = (x + zerg) % n;
      ll q = 0;
      if (x == find(x)) {
        q = dsu[(int) x].second;
      } else {
        q = dsu[(int) x].second + dsu[(int) find(x)].second;
      }
      q -= read[(int) x];
      read[(int) x] += q;
      zerg = ((ll) 100500 * zerg + q) % p;
      cout << q << '\n';
    }
  }
  return 0;
}
