#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>

typedef long long ll;

const ll INF = (ll) 1e18;
const int MAXN = 105;

struct edge {
    int from, to, index;
    ll c, flow, cost;
};

typedef std::vector<edge> ve;
typedef std::vector<edge*> vptre;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int n;
vi graph[MAXN];
std::vector<ll> dist;

inline void add_edge(ve &edges, int from, int to, ll c, ll cost) {
    edge e1 = {from, to, (int) edges.size(), c, 0, cost};
    edge e2 = {to, from, (int) edges.size() + 1, 0, 0, -cost};

    graph[from].push_back(e1.index);
    edges.push_back(e1);
    graph[to].push_back(e2.index);
    edges.push_back(e2);
}

inline bool bfs(ve &edges, vptre &parent) {
    std::queue<int> q;
    q.push(0);

    dist.assign(n, INF);

    dist[0] = 0;

    int t = n - 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int pos : graph[cur]) {
            edge e = edges[pos];
            if (dist[e.to] > dist[cur] + e.cost && e.flow < e.c) {
                q.push(e.to);
                dist[e.to] = dist[cur] + e.cost;
                parent[e.to] = &edges[pos];
            }
        }
    }

    return dist[t] != INF;
}

inline std::pair<ll, ll> dfs(ve &edges, vptre &parent, int cur, ll cur_cost) {
    if (cur == 0) {
        return {cur_cost, 0};
    }

    edge *cur_edge = parent[cur];

    std::pair<ll, ll> delta = dfs(edges, parent, cur_edge->from,
     std::min(cur_cost, cur_edge->c - cur_edge->flow));

    if (delta.first > 0) {
        cur_edge->flow += delta.first;
        edges[cur_edge->index ^ 1].flow -= delta.first;
        delta.second += delta.first * cur_edge->cost;
    }

    return delta;
}

inline ll dinic(ve &edges) {
    ll max_flow = 0;

    vptre parent(n);
    while (bfs(edges, parent)) {
        std::pair<ll, ll> cur_flow = dfs(edges, parent, n - 1, INF);
        max_flow += cur_flow.second;
    }

    return max_flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int m;
    std::cin >> n >> m;

    ve edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c, cost;
        std::cin >> u >> v >> c >> cost;

        add_edge(edges, u - 1, v - 1, c, cost);
    }

    std::cout << dinic(edges);

    return 0;
}
