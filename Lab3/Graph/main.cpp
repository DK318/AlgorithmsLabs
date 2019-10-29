#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, m, k;
vector<int> dsu, sz;
vector<pair<int, pair<int, int> > > queries;

void build() {
  dsu.resize(n);
  sz.resize(n, 1);
  for (int i = 0; i < n; i++) {
    dsu[i] = i;
  }
}

int find(int x) {
  return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) {
    return;
  }
  if (sz[x] < sz[y]) {
    swap(x, y);
  }
  dsu[y] = x;
  sz[x] += sz[y];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m >> k;
  build();
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
  }
  for (int i = 0; i < k; i++) {
    string type; int u, v; cin >> type >> u >> v;
    u--; v--;
    if (type == "cut") {
      queries.push_back({0, {u, v}});
    } else {
      queries.push_back({1, {u, v}});
    }
  }
  vector<bool> ans;
  for (int i = k - 1; i >= 0; i--) {
    int u = queries[i].second.first, v = queries[i].second.second;
    if (queries[i].first == 0) {
      unite(u, v);
    } else {
      u = find(u); v = find(v);
      if (u == v) {
        ans.push_back(true);
      } else {
        ans.push_back(false);
      }
    }
  }
  for (int i = (int) ans.size() - 1; i >= 0; i--) {
    cout << (ans[i] ? "YES\n" : "NO\n");
  }
  return 0;
}
