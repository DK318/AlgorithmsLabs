#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n;
vector<int> dsu;

void build() {
  dsu.resize(n);
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
  dsu[x] = y;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n;
  build();
  for (int i = 0; i < n; i++) {
    int q; cin >> q;
    int ans = find(q - 1);
    cout << ans + 1 << ' ';
    if (ans == n - 1) {
      unite(ans, 0);
    } else {
      unite(ans, ans + 1);
    }
  }
  return 0;
}
