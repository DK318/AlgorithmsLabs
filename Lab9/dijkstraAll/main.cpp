#include <iostream>
#include <vector>
#include <utility>
#include <set>

const long long INF = (long long) 1e18;

typedef std::pair<long long, int> pli;
typedef std::vector<long long> vl;
typedef std::vector<pli> vpli;
typedef std::vector<vpli> vvpli;

void dijkstra(vvpli &graph, vl &dist) {
    dist[0] = 0;
    std::set<pli> s;
    s.insert({0, 0});
    while (!s.empty()) {
        int cur = s.begin()->second;
        s.erase(s.begin());
        for (pli to : graph[cur]) {
            if (dist[cur] + to.first < dist[to.second]) {
                s.erase({dist[to.second], to.second});
                dist[to.second] = dist[cur] + to.first;
                s.insert({dist[to.second], to.second});
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    vvpli graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        graph[u - 1].push_back({w, v - 1});
        graph[v - 1].push_back({w, u - 1});
    }
    vl ans(n, INF);
    dijkstra(graph, ans);
    for (long long cur : ans) {
        std::cout << cur << ' ';
    }
    return 0;
}
