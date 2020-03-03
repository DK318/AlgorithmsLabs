#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

struct node {
  ll key;
  int priority;
  ll sum;
  node *left = nullptr;
  node *right = nullptr;
  node(ll key) : key(key) {
    priority = rand();
    sum = key;
  }
};

node *treap;

ll get_sum(node* x) {
  return x == nullptr ? 0 : x->sum;
}

void update_sum(node *x) {
  if (x != nullptr) {
    x->sum = x->key + get_sum(x->left) + get_sum(x->right);
  }
}

node* merge(node *t1, node *t2) {
  if (t1 == nullptr || t2 == nullptr) {
    return t1 == nullptr ? t2 : t1;
  }
  if (t1->priority > t2->priority) {
    t1->right = merge(t1->right, t2);
    update_sum(t1);
    return t1;
  } else {
    t2->left = merge(t1, t2->left);
    update_sum(t2);
    return t2;
  }
}

void split(node *root, ll key, node *&l, node *&r) {
  if (root == nullptr) {
    l = r = nullptr;
  } else if (root->key < key) {
    split(root->right, key, root->right, r);
    l = root;
  } else {
    split(root->left, key, l, root->left);
    r = root;
  }
  update_sum(l);
  update_sum(r);
}

bool contains(ll key) {
  node *t1, *t2, *t3;
  split(treap, key, t1, t2);
  split(t2, key + 1, t2, t3);
  bool res = (t2 != nullptr);
  t1 = merge(t1, t2);
  treap = merge(t1, t3);
  return res;
}

void insert(ll key) {
  if (contains(key)) {
    return;
  }
  node *t1, *t2;
  split(treap, key, t1, t2);
  treap = merge(t1, new node(key));
  treap = merge(treap, t2);
}

ll range_sum(ll l, ll r) {
  node *t1, *t2, *t3;
  split(treap, l, t1, t2);
  split(t2, r + 1, t2, t3);
  ll ans = get_sum(t2);
  t1 = merge(t1, t2);
  treap = merge(t1, t3);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  srand(time(0));
  int n;
  cin >> n;
  bool was_last_sum = false;
  ll last_sum = 0;
  for (int i = 0; i < n; i++) {
    char query;
    cin >> query;
    if (query == '+') {
      ll x;
      cin >> x;
      if (was_last_sum) {
        x = (last_sum + x) % 1000000000;
      }
      was_last_sum = false;
      insert(x);
    } else {
      ll l, r;
      cin >> l >> r;
      was_last_sum = true;
      last_sum = range_sum(l, r);
      cout << last_sum << '\n';
    }
  }
  return 0;
}
