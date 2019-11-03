#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, q;
vector<int> dsu1, dsu2;

void build() {
  dsu1.resize(n);
  dsu2.resize(n);
  for (int i = 0; i < n; i++) {
    dsu1[i] = i;
    dsu2[i] = i;
  }
}

int find1(int x) {
  return dsu1[x] == x ? x : dsu1[x] = find1(dsu1[x]);
}

int find2(int x) {
  return dsu2[x] == x ? x : dsu2[x] = find2(dsu2[x]);
}

void unite2(int x, int y) {
  x = find2(x); y = find2(y);
  if (x == y) {
    return;
  }
  dsu2[x] = y;
}

void unite1(int x, int y) {
  x = find1(x); y = find1(y);
  if (x == y) {
    return;
  }
  dsu1[x] = y;
}

void multiunite(int x, int y) {
  while (x < y) {
    x = find2(x);
    if (x >= y) {
      return;
    }
    unite2(x, x + 1);
    unite1(x, x + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> q;
  build();
  for (int i = 0; i < q; i++) {
    int type, u, v;
    cin >> type >> u >> v;
    u--; v--;
    if (type == 1) {
      if (u > v) {
        swap(u, v);
      }
      unite1(u, v);
    }
    if (type == 2) {
      multiunite(u, v);
    }
    if (type == 3) {
      u = find1(u); v = find1(v);
      if (u == v) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }
  return 0;
}
