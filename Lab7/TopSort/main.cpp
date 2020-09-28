#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool dfs(vvi &graph, vi &colors, vi &topsort, int cur) {
    colors[cur] = GRAY;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (colors[to] == GRAY) {
            return true;
        } else if (colors[to] == WHITE) {
            if (dfs(graph, colors, topsort, to)) {
                return true;
            }
        }
    }
    colors[cur] = BLACK;
    topsort.push_back(cur + 1);
    return false;
}

bool build_topsort(vvi &graph, vi &topsort) {
    vi colors(graph.size(), WHITE);
    for (size_t i = 0; i < graph.size(); i++) {
        if (colors[i] == WHITE) {
            if (dfs(graph, colors, topsort, i)) {
                return false;
            }
        }
    }
    std::reverse(topsort.begin(), topsort.end());
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
    }
    vi ans;
    if (build_topsort(graph, ans)) {
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << ' ';
        }
    } else {
        std::cout << -1;
    }
    return 0;
}
