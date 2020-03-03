#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

struct node {
  int key;
  int priority;
  int position;
  node *left = nullptr;
  node *right = nullptr;
  node *parent = nullptr;
  node(int key, int priority, int position)
      : key(key), priority(priority), position(position) {}
};

node *treap = nullptr, *last_node = nullptr;
vector<pair<pair<int, int>, int> > ans, keys_and_priorities;

int get_position(node *x) {
  return x == nullptr ? 0 : x->position;
}

void insert(node *n) {
  if (treap == nullptr) {
    treap = n;
    last_node = n;
    return;
  }
  while (last_node != treap && last_node->priority > n->priority) {
    last_node = last_node->parent;
  }
  if (last_node == treap && treap->priority > n->priority) {
    treap->parent = n;
    n->left = treap;
    treap = n;
  } else {
    node *tmp = last_node->right;
    last_node->right = n;
    n->parent = last_node;
    n->left = tmp;
    if (tmp != nullptr) {
      n->left->parent = n;
    }
  }
  last_node = n;
}

void make_ans(node *current) {
  if (current != nullptr) {
    make_ans(current->left);
    ans[current->position].first.first = get_position(current->parent);
    ans[current->position].first.second = get_position(current->left);
    ans[current->position].second = get_position(current->right);
    make_ans(current->right);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  ans.resize(n + 1);
  keys_and_priorities.resize(n);
  for (int i = 0; i < n; i++) {
    int key, priority;
    cin >> key >> priority;
    keys_and_priorities[i] = {{key, priority}, i + 1};
  }
  sort(keys_and_priorities.begin(), keys_and_priorities.end());
  for (int i = 0; i < n; i++) {
    pair<pair<int, int>, int> cur = keys_and_priorities[i];
    insert(new node(cur.first.first, cur.first.second, cur.second));
  }
  make_ans(treap);
  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    pair<pair<int, int>, int> cur = ans[i];
    cout << cur.first.first << ' ' << cur.first.second << ' ' << cur.second << '\n';
  }
  return 0;
}
