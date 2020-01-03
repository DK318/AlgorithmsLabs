#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << "18 153\n";
  for (int i = 0; i < 18; i++) {
    for (int j = i + 1; j < 18; j++) {
      cout << i + 1 << ' ' << j + 1 << ' ' << "1\n";
    }
  }
  return 0;
}
