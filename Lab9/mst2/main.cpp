#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
    int w, from, to;
};

typedef std::vector<int> vi;
typedef std::vector<edge> v_edges;

int find_set(vi &sets, int cur) {
    return sets[cur] == cur ? cur : sets[cur] = find_set(sets, sets[cur]);
}

void unite(vi &sets, vi &rank, int x, int y) {
    x = find_set(sets, x);
    y = find_set(sets, y);
    if (x != y) {
        if (rank[x] < rank[y]) {
            std::swap(x, y);
        }
        sets[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    v_edges edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges.push_back({w, u - 1, v - 1});
    }
    vi sets(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        sets[i] = i;
    }
    std::sort(edges.begin(), edges.end(), [](edge lhs, edge rhs) {return lhs.w < rhs.w;});
    int ans = 0;
    for (edge cur : edges) {
        int x = cur.from, y = cur.to;
        if (find_set(sets, x) != find_set(sets, y)) {
            ans += cur.w;
            unite(sets, rank, x, y);
        }
    }
    std::cout << ans;
    return 0;
}
