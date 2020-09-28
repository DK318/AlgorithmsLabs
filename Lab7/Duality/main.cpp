#include <iostream>
#include <cstdlib>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool dfs(vvi &graph, vi &colors, bool color, int cur) {
    colors[cur] = color;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (colors[to] == -1) {
            if (!dfs(graph, colors, !color, to)) {
                return false;
            }
        } else if (colors[to] == color) {
            return false;
        }
    }
    return true;
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
    vi colors(n, -1);
    for (int i = 0; i < n; i++) {
        if (colors[i] == -1) {
            if (!dfs(graph, colors, false, i)) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES";
    return 0;
}
