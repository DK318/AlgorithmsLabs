#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

int n;
vector<ll> a, b;
vector<vector<pair<int, ll> > > graph;

void distributed_file_system(int u, int from) {
  for (int i = 0; i < (int) graph[u].size(); i++) {
    int to = graph[u][i].first;
    if (to != from) {
      distributed_file_system(to, u);
    }
  }
  a[u] = 0;
  b[u] = 0;
  for (int i = 0; i < (int) graph[u].size(); i++) {
    int to = graph[u][i].first;
    if (to != from) {
      a[u] += max(a[to], b[to]);
    }
  }
  for (int i = 0; i < (int) graph[u].size(); i++) {
    int to = graph[u][i].first;
    ll w = graph[u][i].second;
    if (to != from) {
      b[u] = max(b[u], w + a[to] - max(a[to], b[to]));
    }
  }
  b[u] += a[u];
}

int main() {
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n;
  graph.resize(n);
  a.resize(n);
  b.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    ll w; cin >> u >> v >> w;
    u--; v--;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }
  distributed_file_system(0, 0);
  cout << max(a[0], b[0]);
  return 0;
}
