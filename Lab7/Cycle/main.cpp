#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool dfs(vvi &graph, vi &colors, vi &parents, int &start, int &finish, int cur) {
    colors[cur] = GRAY;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i];
        if (colors[to] == GRAY) {
            start = to;
            finish = cur;
            return true;
        }
        if (colors[to] == WHITE) {
            parents[to] = cur;
            if (dfs(graph, colors, parents, start, finish, to)) {
                return true;
            }
        }
    }
    colors[cur] = BLACK;
    return false;
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
    vi colors(n, WHITE), parents(n);
    int start = -1, finish = -1;
    for (int i = 0; i < n; i++) {
        if (colors[i] == WHITE) {
            if (dfs(graph, colors, parents, start, finish, i)) {
                break;
            }
        }
    }
    if (start == -1) {
        std::cout << "NO";
    } else {
        std::cout << "YES\n";
        vi cycle;
        for (int cur = finish; cur != start; cur = parents[cur]) {
            cycle.push_back(cur);
        }
        cycle.push_back(start);
        std::reverse(cycle.begin(), cycle.end());
        for (size_t i = 0; i < cycle.size(); i++) {
            std::cout << cycle[i] + 1 << ' ';
        }
    }
    return 0;
}
