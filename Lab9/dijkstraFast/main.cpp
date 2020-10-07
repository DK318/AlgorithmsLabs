#include <iostream>
#include <vector>
#include <utility>
#include <set>

const long long INF = (long long) 1e18;

typedef std::pair<long long, int> pli;
typedef std::vector<long long> vl;
typedef std::vector<pli> vpli;
typedef std::vector<vpli> vvpli;

long long dijkstra(vvpli &graph, int start, int finish) {
    vl dist(graph.size(), INF);
    dist[start] = 0;
    std::set<pli> s;
    s.insert({0, start});
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
    long long res = dist[finish];
    return res == INF ? -1 : res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, s, f;
    std::cin >> n >> s >> f;
    s--;
    f--;
    vvpli graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long w;
            std::cin >> w;
            if (w > 0) {
                graph[i].push_back({w, j});
            }
        }
    }
    std::cout << dijkstra(graph, s, f);
    return 0;
}
