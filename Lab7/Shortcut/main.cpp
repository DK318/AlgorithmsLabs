#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>

const int INF = 1e9;

typedef std::vector<int> vi;
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<vpii> vvpii;

void dfs(vvpii &graph, vi &colors, vi &topsort, int cur) {
    colors[cur] = true;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        int to = graph[cur][i].first;
        if (!colors[to]) {
            dfs(graph, colors, topsort, to);
        }
    }
    topsort.push_back(cur);
}

void build_topsort(vvpii &graph, vi &topsort) {
    vi colors(graph.size(), false);
    for (size_t i = 0; i < graph.size(); i++) {
        if (!colors[i]) {
            dfs(graph, colors, topsort, i);
        }
    }
    std::reverse(topsort.begin(), topsort.end());
}

int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    s--;
    t--;
    vvpii graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
    }
    vi topsort, reachable(n, false);
    dfs(graph, reachable, topsort, s);
    topsort.clear();
    if (!reachable[t]) {
        std::cout << "Unreachable";
        return 0;
    }
    vvpii reachable_from_start(n);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            continue;
        }
        for (size_t j = 0; j < graph[i].size(); j++) {
            pii to = graph[i][j];
            if (reachable[to.first]) {
                reachable_from_start[i].push_back(to);
            }
        }
    }
    build_topsort(reachable_from_start, topsort);
    vi d(n, INF);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < reachable_from_start[topsort[i]].size(); j++) {
            pii to = reachable_from_start[topsort[i]][j];
            d[to.first] = std::min(d[to.first], d[topsort[i]] + to.second);
        }
    }
    std::cout << d[t];
    return 0;
}
