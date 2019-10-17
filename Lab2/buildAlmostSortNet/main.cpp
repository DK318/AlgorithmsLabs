#include <bits/stdc++.h>

using namespace std;

bool check_sorted(vector<int> x) {
  for (int i = 1; i < (int) x.size(); i++) {
    if (x[i] < x[i - 1]) {
      return false;
    }
  }
  return true;
}

vector<pair<int, int> > build(vector<int> x) {
  vector<pair<int, int> > comparators;
  int pos = 0, n = x.size();
  for (int i = 0; i < n; i++) {
    if (x[i] == 1) {
      pos = i;
      break;
    }
  }
  int cnt = 0;
  vector<int> onePos;
  for (int i = pos + 1; i < n; i++) {
    if (x[i] == 1) {
      cnt++;
      onePos.push_back(i);
    }
  }
  for (int i = 0; i < cnt; i++) {
    comparators.push_back({pos, onePos[i]});
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (j == pos) {
        continue;
      }
      if (j + 1 == pos) {
        if (j + 2 < n) {
          comparators.push_back({j, j + 2});
        }
      } else {
        comparators.push_back({j, j + 1});
      }
    }
  }
  for (int i = 0; i < pos; i++) {
    comparators.push_back({i, pos});
  }
  for (int i = pos + 1; i < n; i++) {
    if (i == n - cnt - 1) {
      continue;
    }
    comparators.push_back({pos, i});
  }
  for (int i = n - 1; i >= pos + 1; i--) {
    if (i == n - cnt - 1) {
      continue;
    }
    comparators.push_back({pos, i});
  }
  for (int i = pos - 1; i >= 0; i--) {
    comparators.push_back({i, pos});
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (j == n - cnt - 1) {
        continue;
      }
      if (j + 1 == n - cnt - 1) {
        if (j + 2 < n) {
          comparators.push_back({j, j + 2});
        }
      } else {
        comparators.push_back({j, j + 1});
      }
    }
  }
  return comparators;
}

int main() {
  /*ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);*/
  while (true) {
    int n; cin >> n;
    if (n == 0) {
      break;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    if (check_sorted(a)) {
      cout << -1 << '\n';
      continue;
    }
    vector<pair<int, int> > comparators = build(a);
    cout << comparators.size() << '\n';
    for (int i = 0; i < (int) comparators.size(); i++) {
      cout << comparators[i].first + 1 << ' ' << comparators[i].second + 1 << '\n';
    }
  }
  return 0;
}
