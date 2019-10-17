#include <bits/stdc++.h>

using namespace std;

const double EPS = 0.000001;

int n, k;

double comp(pair<int, int> arg, double ans) {
  return (double) arg.first - ans * (double) arg.second;
}

double mergeSort(vector<pair<pair<int, int>, int> > &x, double ans) {
  if (x.size() < 2) {
    if (x.size() == 0) {
      return 0;
    }
    return comp(x[0].first, ans);
  }
  vector<pair<pair<int, int>, int> > b, c;
  int mid = x.size() / 2;
  for (int i = 0; i < mid; i++) {
    b.push_back(x[i]);
  }
  for (size_t i = mid; i < x.size(); i++) {
    c.push_back(x[i]);
  }
  mergeSort(b, ans);
  mergeSort(c, ans);
  int l = 0, r = 0, i = 0;
  double res = 0;
  while (l < mid && r < (int) c.size()) {
    if (comp(b[l].first, ans) <= comp(c[r].first, ans)) {
      if (i >= n - k) {
        res += comp(b[l].first, ans);
      }
      x[i++] = b[l++];
    } else {
      if (i >= n - k) {
        res += comp(c[r].first, ans);
      }
      x[i++] = c[r++];
    }
  }
  while (l < mid) {
    if (i >= n - k) {
      res += comp(b[l].first, ans);
    }
    x[i++] = b[l++];
  }
  while (r < (int) c.size()) {
    if (i >= n - k) {
      res += comp(c[r].first, ans);
    }
    x[i++] = c[r++];
  }
  return res;
}

void binary(vector<pair<pair<int, int>, int> > &x) {
  double l = 0, r = 1e6;
  while (r - l > EPS) {
    double mid = (l + r) / 2;
    double check = mergeSort(x, mid);
    if (check >= 0) {
      l = mid;
    } else {
      r = mid;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  vector<pair<pair<int, int>, int> > a(n);
  for (int i = 0; i < n; i++) {
    int v, w;
    cin >> v >> w;
    a[i] = make_pair(make_pair(v, w), i + 1);
  }
  binary(a);
  for (int i = n - 1; i >= n - k; i--) {
    cout << a[i].second << ' ';
  }
  return 0;
}
