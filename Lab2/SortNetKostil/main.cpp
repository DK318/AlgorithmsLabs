#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int> > > sortNet{{{1, 2}, {3, 4}, {5, 6}, {7, 8},
                                          {9, 10}, {11, 12}, {13, 14}, {15, 16}},
                                         {{1, 4}, {2, 3}, {5, 8}, {6, 7},
                                          {9, 12}, {10, 11}, {13, 16}, {14, 15}},
                                         {{1, 2}, {3, 4}, {5, 6}, {7, 8},
                                          {9, 10}, {11, 12}, {13, 14}, {15, 16}},
                                         {{1, 8}, {2, 7}, {3, 6}, {4, 5},
                                          {9, 16}, {10, 15}, {11, 14}, {12, 13}},
                                         {{1, 3}, {2, 4}, {5, 7}, {6, 8},
                                          {9, 11}, {10, 12}, {13, 15}, {14, 16}},
                                         {{1, 2}, {3, 4}, {5, 6}, {7, 8},
                                          {9, 10}, {11, 12}, {13, 14}, {15, 16}},
                                         {{1, 16}, {2, 15}, {3, 14}, {4, 13},
                                          {5, 12}, {6, 11}, {7, 10}, {8, 9}},
                                         {{1, 5}, {2, 6}, {3, 7}, {4, 8},
                                          {9, 13}, {10, 14}, {11, 15}, {12, 16}},
                                         {{1, 3}, {2, 4}, {5, 7}, {6, 8},
                                          {9, 11}, {10, 12}, {13, 15}, {14, 16}},
                                         {{1, 2}, {3, 4}, {5, 6}, {7, 8},
                                          {9, 10}, {11, 12}, {13, 14}, {15, 16}}};
vector<vector<pair<int, int> > > ansNet;
int n, cntcomps = 0;

void build() {
  for (int i = 0; i < (int) sortNet.size(); i++) {
    vector<pair<int, int> > layer;
    for (int j = 0; j < (int) sortNet[i].size(); j++) {
      pair<int, int> comparator = sortNet[i][j];
      if (comparator.first <= n && comparator.second <= n) {
        layer.push_back(comparator);
        cntcomps++;
      }
    }
    if ((int) layer.size() != 0) {
      ansNet.push_back(layer);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  build();
  /*cout << n << ' ' << cntcomps << ' ' << ansNet.size() << '\n';
  for (int i = 0; i < (int) ansNet.size(); i++) {
    cout << ansNet[i].size() << ' ';
    for (int j = 0; j < (int) ansNet[i].size(); j++) {
      cout << ansNet[i][j].first << ' ' << ansNet[i][j].second << ' ';
    }
    cout << '\n';
  }*/
  cout << -2 % 6;
  return 0;
}
