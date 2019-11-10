#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int n, m;

int cnt_k() {
  double k = sqrt(m * (log(m) / log(2))) / 4;
  int res = static_cast<int>(k);
  if ((double) res != k) {
    res++;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  if (m <= 16) {
    for (int i = 0; i < m; i++) {
      cout << "0 1 1\n";
    }
    return 0;
  }
  int k = cnt_k(), cnt = 0;
  int cur = k + 1;
  for (int i = 1; i <= k; i++) {
    cout << "1 " << cur << ' ' << i << '\n';
    cnt++;
  }
  for (int i = k + 2; i <= 2 * k + 2; i++) {
    cout << "1 " << i << ' ' << cur << '\n';
    cnt++;
    for (int j = 1; j <= k; j += 2) {
      cout << "0 " << j << ' ' << j + 1 << '\n';
      cnt++;
    }
    cur = i;
  }
  for (int i = cnt; i < m; i++) {
    cout << "0 1 1\n";
  }
  return 0;
}
