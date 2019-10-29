#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n; cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    if (2 * i <= n) {
      if (a[i] > a[2 * i]) {
        cout << "NO";
        return 0;
      }
    }
    if ((2 * i) + 1 <= n) {
      if (a[i] > a[(2 * i) + 1]) {
        cout << "NO";
        return 0;
      }
    }
  }
  cout << "YES";
  return 0;
}
