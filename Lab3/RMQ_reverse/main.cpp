#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, m;
vector<int> dsu, ans;
vector<pair<int, pair<int, int> > > ranges;

void build() {
  dsu.resize(n + 1);
  ranges.resize(m);
  ans.resize(n, 0);
  for (int i = 0; i < n + 1; i++) {
    dsu[i] = i;
  }
}

int find(int x) {
  return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

void unite(int x, int y) {
  x = find(x); y = find(y);
  dsu[x] = y;
}

void multiunite(int x, int y, int q) {
  while (x < y) {
    x = find(x);
    if (x >= y) {
      return;
    }
    if (x != n) {
      ans[x] = q;
    }
    unite(x, x + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  build();
  for (int i = 0; i < m; i++) {
    int l, r, q; cin >> l >> r >> q;
    l--; r--;
    ranges[i] = {q, {l, r}};
  }
  sort(ranges.rbegin(), ranges.rend());
  for (int i = 0; i < m; i++) {
    int l = ranges[i].second.first, r = ranges[i].second.second;
    int q = ranges[i].first;
    multiunite(l, r + 1, q);
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}
