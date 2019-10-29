#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

struct Node {
  int num;
  int minn;
  int maxx;
};

int n;
vector<Node> dsu;
vector<int> sz;

void build() {
  dsu.resize(n + 1);
  sz.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    dsu[i].num = i;
    dsu[i].minn = i;
    dsu[i].maxx = i;
    sz[i] = 1;
  }
}

Node find(int x) {
  if (dsu[x].num == x) {
    return dsu[x];
  }
  return dsu[x] = find(dsu[x].num);
}

void unite(int x, int y) {
  Node x_node = find(x), y_node = find(y);
  if (x_node.num == y_node.num) {
    return;
  }
  if (sz[x_node.num] < sz[y_node.num]) {
    swap(x_node, y_node);
  }
  x_node.minn = min(x_node.minn, y_node.minn);
  x_node.maxx = max(x_node.maxx, y_node.maxx);
  dsu[y_node.num] = x_node;
  dsu[x_node.num] = x_node;
  sz[x_node.num] += sz[y_node.num];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n;
  build();
  while (true) {
    string type; cin >> type;
    if (cin.eof()) {
      break;
    }
    if (type == "union") {
      int x, y; cin >> x >> y;
      unite(x, y);
    } else {
      int x; cin >> x;
      Node node = find(x);
      cout << node.minn << ' ' << node.maxx << ' ' << sz[node.num] << '\n';
    }
  }
  return 0;
}
