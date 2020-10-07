#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
    int w, from, to;
};

const int INF = (int) 1e9 + 10;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<edge> v_edges;

int find_set(vi &sets, int cur) {
    return sets[cur] == cur ? cur : sets[cur] = find_set(sets, sets[cur]);
}

void unite(vi &sets, vi &sz, int x, int y) {
    x = find_set(sets, x);
    y = find_set(sets, y);
    if (x != y) {
        if (sz[x] < sz[y]) {
            std::swap(x, y);
        }
        sets[y] = x;
        sz[x] += sz[y];
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
    v_edges edges;
    vvi graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
        edges.push_back({w, u - 1, v - 1});
    }
    vi used(n, false);
    dfs(graph, used, 0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            std::cout << "NO";
            return 0;
        }
    }
    std::sort(edges.begin(), edges.end(), [](edge lhs, edge rhs) {return lhs.w < rhs.w;});
    int ans = 2 * INF + 1;
    for (int it = 0; it < m; it++) {
        vi sets(n), sz(n, 1);
        int min_edge = INF, max_edge = -INF;
        for (int i = 0; i < n; i++) {
            sets[i] = i;
        }
        for (int i = it; i < m; i++) {
            int x = edges[i].from, y = edges[i].to;
            if (find_set(sets, x) != find_set(sets, y)) {
                min_edge = std::min(min_edge, edges[i].w);
                max_edge = std::max(max_edge, edges[i].w);
                unite(sets, sz, x, y);
            }
        }
        if (sz[find_set(sets, 0)] == n) {
            ans = std::min(ans, max_edge - min_edge);
        }
    }
    std::cout << "YES\n" << ans;
    return 0;
}
