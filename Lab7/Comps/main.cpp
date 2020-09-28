#include <iostream>
#include <cstdlib>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs(vvi &graph, vi &used, vi &table, int &comp, int cur) {
    used[cur] = true;
    table[cur] = comp;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (!used[to]) {
            dfs(graph, used, table, comp, to);
        }
    }
}

void make_comps(vvi &graph, vi &table, int &comp) {
    vi used(graph.size(), false);
    for (size_t i = 0; i < graph.size(); i++) {
        if (!used[i]) {
            dfs(graph, used, table, comp, i);
            comp++;
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vvi graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    vi table(n);
    int comp = 1;
    make_comps(graph, table, comp);
    std::cout << comp - 1 << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << table[i] << ' ';
    }
    return 0;
}
