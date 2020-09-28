#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs(vvi &graph, vi &colors, vi &tin, vi &fup, std::set<int> &cutpoints,
 int &timer, int cur, int from) {
     colors[cur] = true;
     tin[cur] = timer;
     fup[cur] = timer++;
     int children = 0;
     for (size_t i = 0; i < graph[cur].size(); i++) {
         int to = graph[cur][i];
         if (to != from) {
             if (colors[to]) {
                 fup[cur] = std::min(fup[cur], tin[to]);
             } else {
                 dfs(graph, colors, tin, fup, cutpoints, timer, to, cur);
                 fup[cur] = std::min(fup[cur], fup[to]);
                 if (fup[to] >= tin[cur] && from != -1) {
                     cutpoints.insert(cur);
                 }
                 children++;
             }
         }
     }
     if (from == -1 && children > 1) {
         cutpoints.insert(cur);
     }
}

void find_cutpoints(vvi &graph, std::set<int> &cutpoints) {
    int timer = 0;
    vi colors(graph.size(), false), tin(graph.size()), fup(graph.size());
    for (size_t i = 0; i < graph.size(); i++) {
        if (!colors[i]) {
            dfs(graph, colors, tin, fup, cutpoints, timer, i, -1);
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
    std::set<int> cutpoints;
    find_cutpoints(graph, cutpoints);
    std::cout << cutpoints.size() << '\n';
    for (auto i = cutpoints.begin(); i != cutpoints.end(); i++) {
        std::cout << *i + 1 << ' ';
    }
    return 0;
}
