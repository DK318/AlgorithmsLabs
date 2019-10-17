#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll SZ = (ll)1e18;

ll x, c;
int m;

void binary() {
  ll l = max(x - m - 1, 0ll), r = min(x + 1, SZ - m + 1);
  while (l < r - 1) {
    ll mid = (l + r) / 2;
    cout << "? " << mid << endl;
    ll q;
    cin >> q;
    q -= c;
    if (q < 1) {
      q += SZ;
    }
    if (q == x) {
      cout << "! " << mid << endl;
      return;
    }
    if (q < x) {
      l = mid;
    }
    if (q > x) {
      r = mid;
    }
  }
  cout << "! -1" << endl;
}

int main() {
  cin >> x >> m;
  cout << "? 1" << endl;
  cin >> c;
  if (c == x) {
    cout << "! 1" << endl;
    return 0;
  }
  c--;
  x -= c;
  if (x < 1) {
    x += SZ;
  }
  binary();
  return 0;
}
