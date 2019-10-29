#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int INF = INT_MAX;

vector<int> pos;
vector<pair<int, int> > heap_arr;

void sift_down(int i) {
  while (2 * i + 1 < (int) heap_arr.size()) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
    if (right < (int) heap_arr.size()) {
      if (heap_arr[right].first < heap_arr[left].first) {
        j = right;
      }
    }
    if (heap_arr[i].first <= heap_arr[j].first) {
      break;
    }
    swap(heap_arr[i], heap_arr[j]);
    swap(pos[heap_arr[i].second], pos[heap_arr[j].second]);
    i = j;
  }
}

void sift_up(int i) {
  while (heap_arr[i].first < heap_arr[(i - 1) / 2].first) {
    swap(heap_arr[i], heap_arr[(i - 1) / 2]);
    swap(pos[heap_arr[i].second], pos[heap_arr[(i - 1) / 2].second]);
    i = (i - 1) / 2;
  }
}

pair<int, int> extract_min() {
  pos.push_back(-1);
  if (heap_arr.size() == 0) {
    return {INF, INF};
  }
  pair<int, int> res = heap_arr[0];
  swap(heap_arr[0], heap_arr[heap_arr.size() - 1]);
  swap(pos[heap_arr[0].second], pos[heap_arr[heap_arr.size() - 1].second]);
  heap_arr.erase(heap_arr.end() - 1);
  sift_down(0);
  return res;
}

void push(int x) {
  pair<int, int> z = {x, pos.size()};
  pos.push_back(heap_arr.size());
  heap_arr.push_back(z);
  sift_up(heap_arr.size() - 1);
}

void decrease_key(int key, int val) {
  pos.push_back(-1);
  int i = pos[key];
  if (i == -1) {
    return;
  }
  heap_arr[i].first = val;
  sift_up(i);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  while (true) {
    string type; cin >> type;
    if (cin.eof()) {
      return 0;
    }
    if (type == "extract-min") {
      pair<int, int> res = extract_min();
      if (res.first == INF) {
        cout << "*" << '\n';
      } else {
        cout << res.first << ' ' << res.second + 1 << '\n';
      }
    } else if (type == "push") {
      int val; cin >> val;
      push(val);
    } else {
      int key, val; cin >> key >> val;
      decrease_key(key - 1, val);
    }
  }
}
