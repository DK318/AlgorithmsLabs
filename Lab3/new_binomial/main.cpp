#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int SZ = 25;

struct Node {
  pair<int, int> key;
  int degree;
  Node* parent;
  Node* child;
  Node* sibling;
};

struct binomial_heap {
  Node* root_list[SZ];
};

Node* create_node(int val, int num) {
  Node* np = new Node;
  np->key = {val, num};
  np->degree = 0;
  np->parent = NULL;
  np->child = NULL;
  np->sibling = NULL;
  return np;
}

binomial_heap make_heap() {
  binomial_heap res;
  for (int i = 0; i < SZ; i++) {
    res.root_list[i] = NULL;
  }
  return res;
}

Node* join(Node* x, Node* y) {
  if (x->key.first > y->key.first) {
    swap(x, y);
  }
  y->sibling = x->child;
  y->parent = x;
  x->child = y;
  return x;
}

binomial_heap merge(binomial_heap h1, binomial_heap h2) {
  binomial_heap res = make_heap();
  int pos = 0;
  for (int i = 0; i < SZ; i++) {
    Node* h1_node = h1.root_list[i];
    Node* h2_node = h2.root_list[i];
    if (h1_node != NULL && h2_node != NULL) {
      res.root_list[++pos] = join(h1_node, h2_node);
    } else if (res.root_list[pos] != NULL) {
      if (h1_node != NULL) {
        res.root_list[++pos] = join(h1_node, res.root_list[pos]);
        res.root_list[pos - 1] = NULL;
      } else if (h2_node != NULL) {
        res.root_list[++pos] = join(h2_node, res.root_list[pos]);
        res.root_list[pos - 1] = NULL;
      } else {
        pos++;
      }
    } else {
      if (h1_node != NULL) {
        res.root_list[pos++] = h1_node;
      } else {
        res.root_list[pos++] = h2_node;
      }
    }
  }
  return res;
}

binomial_heap insert(binomial_heap h, int val, int num) {
  Node* p = create_node(val, num);
  binomial_heap h1 = make_heap();
  h1.root_list[0] = p;
  return merge(h1, h);
}

int get_min(binomial_heap h) {
  int minn = INT_MAX;
  for (int i = 0; i < SZ; i++) {
    if (h.root_list[i] != NULL) {
      minn = min(minn, h.root_list[i]->key.first);
    }
  }
  return minn;
}

vector<Node*> make_root_list(Node* p) {
  vector<Node*> res;
  if (p->child == NULL) {
    return res;
  }
  res.push_back(p->child);
  while (res[res.size() - 1]->sibling != NULL) {
    res.push_back(res[res.size() - 1]->sibling);
  }
  reverse(res.begin(), res.end());
  return res;
}

binomial_heap extract_min(binomial_heap h) {
  binomial_heap res = make_heap();
  int pos = -1, minn = INT_MAX, num = INT_MAX;
  for (int i = 0; i < SZ; i++) {
    if (h.root_list[i] == NULL) {
      continue;
    }
    if (h.root_list[i]->key.first < minn) {
      if (h.root_list[i]->key.second < num) {
        minn = h.root_list[i]->key.first;
        num = h.root_list[i]->key.second;
        pos = i;
      }
    }
  }
  Node* p = h.root_list[pos];
  vector<Node*> children = make_root_list(p);
  for (int i = 0; i < (int) children.size(); i++) {
    res.root_list[i] = children[i];
  }
  h.root_list[pos] = NULL;
  return merge(res, h);
}

Node* find(Node* h, int num) {
  Node* x = h;
  Node* p = NULL;
  if (x->key.second == num) {
    p = x;
    return p;
  }
  if (x->child != NULL && p == NULL) {
    p = find(x->child, num);
  }
  if (x->sibling != NULL && p == NULL) {
    p = find(x->sibling, num);
  }
  return p;
}

binomial_heap decrease_key(binomial_heap h, int num, int val) {
  for (int i = 0; i < SZ; i++) {
    Node* p = h.root_list[i];
    if (p == NULL) {
      continue;
    }
    Node* x = find(p, num);
    if (x != NULL) {
      x->key.first = val;
      Node* y = x;
      Node* z = x->parent;
      while (z != NULL && (y->key.first < z->key.first ||
      (y->key.first == z->key.first && y->key.second < z->key.second))) {
        pair<int, int> tmp = y->key;
        y->key = z->key;
        z->key = tmp;
        y = z;
        z = z->parent;
      }
      return h;
    }
  }
}

binomial_heap del(binomial_heap h, int index) {
  binomial_heap res = h;
  res = decrease_key(res, index, INT_MIN);
  res = extract_min(res);
  return res;
}

binomial_heap set_key(binomial_heap h, int index, int val) {
  binomial_heap res = h;
  res = del(res, index);
  res = insert(res, val, index);
  return res;
}

int n, m;
vector<binomial_heap> heaps;

void init() {
  heaps.resize(n);
  for (int i = 0; i < n; i++) {
    heaps[i] = make_heap();
  }
}

int find_heap(int index) {
  for (int j = 0; j < n; j++) {
    for (int z = 0; z < SZ; z++) {
      Node* p = heaps[j].root_list[z];
      if (p != NULL) {
        Node* x = find(p, index);
        if (x != NULL) {
          return j;
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  init();
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    int type; cin >> type;
    if (type == 0) {
      int v, a; cin >> v >> a;
      v--;
      heaps[v] = insert(heaps[v], a, cnt++);
    } else if (type == 1) {
      int a, b; cin >> a >> b;
      a--; b--;
      heaps[b] = merge(heaps[a], heaps[b]);
      heaps[a] = make_heap();
    } else if (type == 2) {
      int index; cin >> index;
      index--;
      int heap_num = find_heap(index);
      heaps[heap_num] = del(heaps[heap_num], index);
    } else if (type == 3) {
      int index, v; cin >> index >> v;
      index--;
      int heap_num = find_heap(index);
      heaps[heap_num] = set_key(heaps[heap_num], index, v);
    } else if (type == 4) {
      int a; cin >> a;
      a--;
      cout << get_min(heaps[a]) << '\n';
    } else if (type == 5) {
      int a; cin >> a;
      a--;
      heaps[a] = extract_min(heaps[a]);
    }
  }
  return 0;
}