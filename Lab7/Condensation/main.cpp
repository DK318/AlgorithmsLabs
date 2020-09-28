#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs_topsort(vvi &graph, vi &used, vi &top_order, int cur) {
    used[cur] = true;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (!used[to]) {
            dfs_topsort(graph, used, top_order, to);
        }
    }
    top_order.push_back(cur);
}

void dfs_comps(vvi &graph_tr, vi &used, vi &comp, int cur) {
    used[cur] = true;
    comp.push_back(cur);
    for (size_t i = 0; i < graph_tr[cur].size(); i++) {
        int to = graph_tr[cur][i];
        if (!used[to]) {
            dfs_comps(graph_tr, used, comp, to);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vvi graph(n), graph_tr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph_tr[v - 1].push_back(u - 1);
    }
    vi used(n, 0), top_order;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs_topsort(graph, used, top_order, i);
        }
    }
    used.assign(n, 0);
    vi ans_table(n);
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = top_order[i];
        if (!used[v]) {
            vi comp;
            dfs_comps(graph_tr, used, comp, v);
            cnt++;
            for (size_t j = 0; j < comp.size(); j++) {
                ans_table[comp[j]] = cnt;
            }
        }
    }
    std::cout << cnt << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << ans_table[i] << ' ';
    }
    return 0;
}
