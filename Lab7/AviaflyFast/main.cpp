#include <iostream>
#include <vector>
#include <cstdlib>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs1(vvi &graph, vi &used, vi &order, int cur) {
    used[cur] = true;
    for (int to : graph[cur]) {
        if (!used[to]) {
            dfs1(graph, used, order, to);
        }
    }
    order.push_back(cur);
}

void dfs2(vvi &graph_tr, vi &used, vi &comp, int cur) {
    used[cur] = true;
    comp.push_back(cur);
    for (int to : graph_tr[cur]) {
        if (!used[to]) {
            dfs2(graph_tr, used, comp, to);
        }
    }
}

bool try_condensate(vvi &graph, vvi &graph_tr) {
    size_t n = graph.size();
    vi order, comp, used(n, false);
    for (size_t i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(graph, used, order, i);
        }
    }
    used.assign(n, false);
    dfs2(graph_tr, used, comp, order[n - 1]);
    return comp.size() == n;
}

void make_graph(vvi &graph, vvi &graph_tr, vvi &matrix, int d) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; i++) {
        graph[i].clear();
        graph_tr[i].clear();
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i != j && matrix[i][j] <= d) {
                graph[i].push_back(j);
                graph_tr[j].push_back(i);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    vvi matrix(n, vi(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
    int l = 0, r = 1e9 + 1;
    vvi graph(n), graph_tr(n);
    while (l + 2 < r) {
        int mid = (l + r) / 2;
        make_graph(graph, graph_tr, matrix, mid);
        if (try_condensate(graph, graph_tr)) {
            r = mid + 1;
        } else {
            l = mid + 1;
        }
    }
    make_graph(graph, graph_tr, matrix, l);
    if (try_condensate(graph, graph_tr)) {
        std::cout << l;
    } else {
        std::cout << l + 1;
    }
    return 0;
}
