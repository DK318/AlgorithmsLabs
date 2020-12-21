#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cstdlib>

const int INF = (int) 1e9;

struct edge {
    int from, to, c, flow;
};

typedef std::vector<edge> ve;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void add_edge(vvi &graph, ve &edges, int from, int to, int c) {
    edge e1 = {from, to, c, 0};
    edge e2 = {to, from, 0, 0};

    graph[from].push_back((int) edges.size());
    edges.push_back(e1);
    graph[to].push_back((int) edges.size());
    edges.push_back(e2);
}

bool bfs(vvi &graph, ve &edges, vi &dist) {
    std::queue<int> q;
    q.push(0);

    dist.assign(graph.size(), INF);
    dist[0] = 0;

    int t = (int) graph.size() - 1;
    while (!q.empty() && dist[t] == INF) {
        int cur = q.front();
        q.pop();

        for (int pos : graph[cur]) {
            edge e = edges[pos];
            if (dist[e.to] == INF && e.flow < e.c) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return dist[t] != INF;
}

int dfs(vvi &graph, ve &edges, vi &dist, vi &pointer, int cur, int cur_flow) {
    int t = (int) graph.size() - 1;
    if (cur_flow == 0) {
        return 0;
    }

    if (cur == t) {
        return cur_flow;
    }

    for (; pointer[cur] < (int) graph[cur].size(); pointer[cur]++) {
        int pos = graph[cur][pointer[cur]];
        edge e = edges[pos];

        if (dist[e.to] != dist[cur] + 1) {
            continue;
        }

        int delta = dfs(graph, edges, dist, pointer, e.to, std::min(cur_flow, e.c - e.flow));
        if (delta > 0) {
            edges[pos].flow += delta;
            edges[pos ^ 1].flow -= delta;
            return delta;
        }
    }

    return 0;
}

int dinic(vvi &graph, ve &edges) {
    int max_flow = 0;

    while (true) {
        vi dist;
        if (!bfs(graph, edges, dist)) {
            break;
        }

        vi pointer(graph.size(), 0);
        int cur_flow = dfs(graph, edges, dist, pointer, 0, INF);

        while (cur_flow != 0) {
            max_flow += cur_flow;
            cur_flow = dfs(graph, edges, dist, pointer, 0, INF);
        }
    }

    return max_flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;

    vvi graph(n);
    ve edges;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        std::cin >> u >> v >> c;

        add_edge(graph, edges, u - 1, v - 1, c);
    }

    std::cout << dinic(graph, edges);

    return 0;
}
