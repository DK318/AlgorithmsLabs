#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <utility>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, ll> pill;
typedef std::vector<pill> vpill;
typedef std::vector<vpill> vvpill;

const ll INF = (ll) 1e18;

std::mt19937 rng(time(0));

struct node {
    int to, priority, where_min;
    ll weight, min_weight, addition;
    node *left = nullptr;
    node *right = nullptr;
    node(int to, ll weight) : to(to), weight(weight) {
        priority = rand();
        addition = 0;
        min_weight = weight;
        where_min = 0;
    }
};

typedef std::pair<int, node*> pin;

ll get_min_weight(node *x) {
    return x == nullptr ? INF : x->min_weight;
}

void push(node *x) {
    if (x != nullptr && x->addition != 0) {
        x->weight += x->addition;
        x->min_weight += x->addition;
        if (x->left != nullptr) {
            x->left->addition += x->addition;
        }
        if (x->right != nullptr) {
            x->right->addition += x->addition;
        }
        x->addition = 0;
    }
}

ll get_addition(node *x) {
    return x == nullptr ? 0 : x->addition;
}

void update(node *x) {
    if (x != nullptr) {
        x->min_weight = x->weight;
        x->where_min = 0;
        ll left_weight = get_min_weight(x->left) + get_addition(x->left);
        ll right_weight = get_min_weight(x->right) + get_addition(x->right);
        if (left_weight < x->min_weight) {
            x->min_weight = left_weight;
            x->where_min = -1;
        }
        if (right_weight < x->min_weight) {
            x->min_weight = right_weight;
            x->where_min = 1;
        }
    }
}

node* merge(node *t1, node *t2) {
    push(t1);
    push(t2);
    if (t1 == nullptr || t2 == nullptr) {
        return t1 == nullptr ? t2 : t1;
    }
    if (t1->priority > t2->priority) {
        t1->right = merge(t1->right, t2);
        update(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        update(t2);
        return t2;
    }
}

node* extract_min(node *cur, int &to, ll &weight) {
    push(cur);
    if (cur->where_min == 0) {
        to = cur->to;
        weight = cur->weight;
        return merge(cur->left, cur->right);
    } else if (cur->where_min == -1) {
        cur->left = extract_min(cur->left, to, weight);
        update(cur);
        return cur;
    } else {
        cur->right = extract_min(cur->right, to, weight);
        update(cur);
        return cur;
    }
}

void add(node *x, ll how_much) {
    if (x != nullptr) {
        x->addition += how_much;
        push(x);
    }
}

int get(vi &sets, int x) {
    return sets[x] == x ? x : sets[x] = get(sets, sets[x]);
}

void unite(vi &sets, vi &rank, std::vector<pin> &info, int x, int y, pin new_info) {
    x = get(sets, x);
    y = get(sets, y);
    if (x != y) {
        if (rank[x] < rank[y]) {
            std::swap(x, y);
        }
        sets[y] = x;
        info[x] = new_info;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

void dfs(vvi &graph, vi &used, int cur) {
    used[cur] = true;
    for (int to : graph[cur]) {
        if (!used[to]) {
            dfs(graph, used, to);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    vvi graph(n);
    vvpill graph_tr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        graph[u - 1].push_back(v - 1);
        graph_tr[v - 1].push_back({u - 1, w});
    }
    vi used(n, false);
    dfs(graph, used, 0);
    for (int cur : used) {
        if (!cur) {
            std::cout << "NO";
            return 0;
        }
    }
    std::vector<pin> info;
    vi sets(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        sets[i] = i;
        used[i] = false;
    }
    for (int i = 0; i < n; i++) {
        node *cur = nullptr;
        for (pill cur_vertex : graph_tr[i]) {
            cur = merge(cur, new node(cur_vertex.first, cur_vertex.second));
        }
        info.push_back({i, cur});
    }
    ll result = 0;
    int k = n;
    vi jump(2 * n);
    for (int v = 0; v < n; v++) {
        if (info[get(sets, v)].first == 0) {
            continue;
        }
        int cur = v;
        used[cur] = true;
        while (true) {
            int to;
            ll weight;
            info[get(sets, cur)].second = extract_min(info[get(sets, cur)].second, to, weight);
            if (get(sets, cur) == get(sets, to)) {
                continue;
            }
            result += weight;
            add(info[get(sets, cur)].second, -weight);
            jump[info[get(sets, cur)].first] = to;
            if (info[get(sets, to)].first == 0) {
                break;
            }
            if (!used[to]) {
                used[to] = true;
                cur = to;
            } else {
                int new_node = k++, cur_node = to;
                info[get(sets, cur)].first = new_node;
                node *treap_node = info[get(sets, cur)].second;
                while (info[get(sets, cur_node)].first != new_node) {
                    int next_node = jump[info[get(sets, cur_node)].first];
                    treap_node = merge(treap_node, info[get(sets, cur_node)].second);
                    unite(sets, rank, info, cur, cur_node, {new_node, treap_node});
                    cur_node = next_node;
                }
            }
        }
        cur = v;
        while (info[get(sets, cur)].first != 0) {
            int next = jump[info[get(sets, cur)].first];
            unite(sets, rank, info, cur, 0, {0, nullptr});
            cur = next;
        }
    }
    std::cout << "YES\n" << result;
    return 0;
}
