#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, m, shift = 0;
vector<pair<int, int> > dsu;
vector<int> rnk, biparite;

void build() {
  dsu.resize(n);
  rnk.resize(n);
  biparite.resize(n);
  for (int i = 0; i < n; i++) {
    dsu[i] = {i, 0};
    rnk[i] = 0;
    biparite[i] = true;
  }
}

pair<int, int> find(int x) {
  if (x != dsu[x].first) {
    int dist = dsu[x].second;
    dsu[x] = find(dsu[x].first);
    dsu[x].second ^= dist;
  }
  return dsu[x];
}

void unite(int x, int y) {
  pair<int, int> comp1, comp2;
  comp1 = find(x); comp2 = find(y);
  x = comp1.first; y = comp2.first;
  int dist1 = comp1.second, dist2 = comp2.second;
  if (x == y) {
    if (dist1 == dist2) {
      biparite[x] = false;
    }
  } else {
    if (rnk[x] < rnk[y]) {
      swap(x, y);
    }
    dsu[y] = {x, dist1 ^ dist2 ^ 1};
    biparite[x] &= biparite[y];
    if (rnk[x] == rnk[y]) {
      rnk[x]++;
    }
  }
}

bool is_biparite(int x) {
  return biparite[find(x).first];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  build();
  for (int i = 0; i < m; i++) {
    int type, a, b;
    cin >> type >> a >> b;
    int x = (a + shift) % n, y = (b + shift) % n;
    if (type == 0) {
      unite(x, y);
    } else {
      if (!is_biparite(x)) {
        cout << "YES\n";
        shift++;
        shift %= n;
      } else {
        pair<int, int> compx = find(x), compy = find(y);
        if (compx.second == compy.second) {
          cout << "YES\n";
          shift++;
          shift %= n;
        } else {
          cout << "NO\n";
        }
      }
    }
  }
  return 0;
}
