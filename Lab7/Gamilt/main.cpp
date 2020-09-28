#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs(vvi &graph, vi &used, vi &topsort, int cur) {
    used[cur] = true;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (!used[to]) {
            dfs(graph, used, topsort, to);
        }
    }
    topsort.push_back(cur);
}

void build_topsort(vvi &graph, vi &topsort) {
    vi used(graph.size(), false);
    for (size_t i = 0; i < graph.size(); i++) {
        if (!used[i]) {
            dfs(graph, used, topsort, i);
        }
    }
    std::reverse(topsort.begin(), topsort.end());
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vvi graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }
    vi topsort;
    build_topsort(graph, topsort);
    for (int i = 1; i < n; i++) {
        int from = topsort[i - 1], to = topsort[i];
        bool f = false;
        for (size_t j = 0; j < graph[from].size(); j++) {
            if (graph[from][j] == to) {
                f = true;
                break;
            }
        }
        if (!f) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
