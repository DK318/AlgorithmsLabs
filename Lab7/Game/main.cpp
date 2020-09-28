#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs(vvi &graph, vi &used, vi &winable, int cur) {
    used[cur] = true;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (!used[to]) {
            dfs(graph, used, winable, to);
        }
        if (!winable[to]) {
            winable[cur] = true;
        }
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    s--;
    vvi graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }
    vi used(n, false), winable(n, false);
    dfs(graph, used, winable, s);
    std::cout << (winable[s] ? "First" : "Second") << " player wins";
    return 0;
}
