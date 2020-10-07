#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

const int INF = (int) 1e9;

typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<pii> vpii;
typedef std::vector<vpii> vvpii;

void ford(vvpii &graph, vi &dist, vi &cycle) {
    size_t n = graph.size();
    dist.assign(n, 0);
    vi parents(n, -1);
    int end_cycle = -1;
    for (size_t i = 0; i < n; i++) {
        end_cycle = -1;
        for (size_t cur = 0; cur < n; cur++) {
            for (pii to : graph[cur]) {
                if (dist[cur] < INF) {
                    if (dist[cur] + to.second < dist[to.first]) {
                        dist[to.first] = std::max(-INF, dist[cur] + to.second);
                        parents[to.first] = cur;
                        end_cycle = to.first;
                    }
                }
            }
        }
    }
    if (end_cycle != -1) {
        int start_cycle = end_cycle;
        for (size_t i = 0; i < n; i++) {
            start_cycle = parents[start_cycle];
        }
        for (int cur = start_cycle; ; cur = parents[cur]) {
            cycle.push_back(cur);
            if (cur == start_cycle && cycle.size() > 1) {
                break;
            }
        }
        std::reverse(cycle.begin(), cycle.end());
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    vvpii graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            std::cin >> w;
            if (w != 0 || w != INF) {
                graph[i].push_back({j, w});
            }
        }
    }
    vi dist(n), cycle;
    ford(graph, dist, cycle);
    if (cycle.size() != 0) {
        std::cout << "YES\n" << cycle.size() << '\n';
        for (int cur : cycle) {
            std::cout << cur + 1 << ' ';
        }
    } else {
        std::cout << "NO";
    }
    return 0;
}
