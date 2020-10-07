#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

const long long INF = (long long) 6e18;

typedef std::pair<int, long long> pil;
typedef std::vector<long long> vl;
typedef std::vector<int> vi;
typedef std::vector<pil> vpil;
typedef std::vector<vpil> vvpil;

void dfs(vvpil &graph, vi &used, int cur) {
    used[cur] = true;
    for (pil to : graph[cur]) {
        if (!used[to.first]) {
            dfs(graph, used, to.first);
        }
    }
}

void ford(vvpil &graph, vl &dist, vi &used, int start) {
    size_t n = graph.size();
    dist.assign(n, INF);
    dist[start] = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t cur = 0; cur < n; cur++) {
            for (pil to : graph[cur]) {
                if (dist[cur] < INF) {
                    if (dist[cur] + to.second < dist[to.first]) {
                        dist[to.first] = std::max(-INF, dist[cur] + to.second);
                        if (i == n - 1) {
                            dfs(graph, used, cur);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m, s;
    std::cin >> n >> m >> s;
    s--;
    vvpil graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
    }
    vl dist(n);
    vi used(n, false);
    ford(graph, dist, used, s);
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            std::cout << "-\n";
        } else if (dist[i] == INF) {
            std::cout << "*\n";
        } else {
            std::cout << dist[i] << '\n';
        }
    }
    return 0;
}
