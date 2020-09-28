#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>

typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<int> vi;
typedef std::vector<vpii> vvpii;

void dfs(vvpii &graph, vi &colors, vi &tin, vi &fup, vi &bridges,
 int &timer, int cur, int from) {
     colors[cur] = true;
     tin[cur] = timer;
     fup[cur] = timer++;
     for (size_t i = 0; i < graph[cur].size(); i++) {
         pii to = graph[cur][i];
         if (to.first != from) {
             if (colors[to.first]) {
                 fup[cur] = std::min(fup[cur], tin[to.first]);
             } else {
                 dfs(graph, colors, tin, fup, bridges, timer, to.first, cur);
                 fup[cur] = std::min(fup[cur], fup[to.first]);
                 if (fup[to.first] > tin[cur]) {
                     bridges.push_back(to.second);
                 }
             }
         }
     }
}

void find_bridges(vvpii &graph, vi &bridges) {
    int timer = 0;
    vi colors(graph.size(), false), tin(graph.size()), fup(graph.size());
    for (size_t i = 0; i < graph.size(); i++) {
        if (!colors[i]) {
            dfs(graph, colors, tin, fup, bridges, timer, i, -1);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vvpii graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back({v - 1, i + 1});
        graph[v - 1].push_back({u - 1, i + 1});
    }
    vi bridges;
    find_bridges(graph, bridges);
    std::cout << bridges.size() << '\n';
    std::sort(bridges.begin(), bridges.end());
    for (size_t i = 0; i < bridges.size(); i++) {
        std::cout << bridges[i] << ' ';
    }
    return 0;
}
