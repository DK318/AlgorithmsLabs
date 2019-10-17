#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<vector<pair<int, int> > > sortnet;

bool check(vector<int> mask) {
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < (int)sortnet[i].size(); j++) {
      int up = sortnet[i][j].first, down = sortnet[i][j].second;
      if (mask[up] > mask[down]) {
        swap(mask[up], mask[down]);
      }
    }
  }
  for (int i = 1; i < n; i++) {
    if (mask[i] < mask[i - 1]) {
      return false;
    }
  }
  return true;
}

vector<int> gen_mask(int x) {
  vector<int> res;
  while (x != 0) {
    res.push_back(x % 2);
    x /= 2;
  }
  while ((int)res.size() != n) {
    res.push_back(0);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  sortnet.resize(k);
  for (int i = 0; i < k; i++) {
    int r;
    cin >> r;
    sortnet[i].resize(r);
    for (int j = 0; j < r; j++) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      if (x > y) {
        swap(x, y);
      }
      sortnet[i][j] = {x, y};
    }
  }
  int masks = (2 << (n - 1));
  for (int i = 0; i < masks; i++) {
    if (!check(gen_mask(i))) {
      //cout << "No";
      //return 0;
      vector<int> z = gen_mask(i);
      for (int i = 0; i < z.size(); i++) {
        cout << z[i] << ' ';
      }
      cout << '\n';
    }
  }
  cout << "Yes";
  return 0;
}