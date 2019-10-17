#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;

unsigned int cur = 0, a, b;
int t, n;

unsigned int nextRand24() {
  cur = cur * a + b;
  return cur >> 8;
}

unsigned int nextRand32() {
  unsigned int a1 = nextRand24(), b1 = nextRand24();
  return (a1 << 8) ^ b1;
}

uint digit(uint x, int pos) {
  if (pos == 0) {
    return (x << 16) >> 16;
  }
  return x >> 16;
}

void bucket_sort(vector<uint> &x) {
  for (int i = 0; i < 2; i++) {
    vector<uint> c(65536, 0);
    for (int j = 0; j < n; j++) {
      uint d = digit(x[j], i);
      c[d]++;
    }
    int cnt = 0;
    for (int j = 0; j < 65536; j++) {
      uint tmp = c[j];
      c[j] = cnt;
      cnt += tmp;
    }
    vector<uint> b(n);
    for (int j = 0; j < n; j++) {
      uint d = digit(x[j], i);
      b[c[d]] = x[j];
      c[d]++;
    }
    x = b;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t >> n >> a >> b;
  vector<uint> arr(n);
  for (int z = 0; z < t; z++) {
    for (int i = 0; i < n; i++) {
      arr[i] = nextRand32();
    }
    bucket_sort(arr);
    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (ll)arr[i] * (ll)(i + 1);
    }
    cout << sum << '\n';
  }
  return 0;
}
