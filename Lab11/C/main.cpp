#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>

typedef long long ll;

const ll INF = (ll) 1e18;
const int MAXN = 505;

struct edge {
    int from, to;
    ll c, flow;
};

typedef std::vector<edge> ve;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int n;
vi graph[MAXN];
int dist[MAXN], pointer[MAXN];

inline void add_edge(ve &edges, int from, int to, ll c) {
    edge e1 = {from, to, c, 0};
    edge e2 = {to, from, 0, 0};

    graph[from].push_back((int) edges.size());
    edges.push_back(e1);
    graph[to].push_back((int) edges.size());
    edges.push_back(e2);
}

inline bool bfs(ve &edges) {
    std::queue<int> q;
    q.push(0);

    memset(dist, -1, n * sizeof(int));
    dist[0] = 0;

    int t = n - 1;
    while (!q.empty() && dist[t] == -1) {
        int cur = q.front();
        q.pop();

        for (int pos : graph[cur]) {
            edge e = edges[pos];
            if (dist[e.to] == -1 && e.flow < e.c) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return dist[t] != -1;
}

inline ll dfs(ve &edges, int cur, ll cur_flow) {
    int t = n - 1;
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

        ll delta = dfs(edges, e.to, std::min(cur_flow, e.c - e.flow));
        if (delta > 0) {
            edges[pos].flow += delta;
            edges[pos ^ 1].flow -= delta;
            return delta;
        }
    }

    return 0;
}

inline ll dinic(ve &edges) {
    ll max_flow = 0;

    while (bfs(edges)) {
        memset(pointer, 0, n * sizeof(int));
        ll cur_flow = dfs(edges, 0, INF);

        while (cur_flow != 0) {
            max_flow += cur_flow;
            cur_flow = dfs(edges, 0, INF);
        }
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
        ll c;
        std::cin >> u >> v >> c;

        add_edge(edges, u - 1, v - 1, c);
        add_edge(edges, v - 1, u - 1, c);
    }

    dinic(edges);

    vi cut;
    for (int i = 0; i < n; i++) {
        if (dist[i] != -1) {
            cut.push_back(i + 1);
        }
    }

    std::cout << cut.size() << '\n';
    for (int cur : cut) {
        std::cout << cur << ' ';
    }

    return 0;
}
