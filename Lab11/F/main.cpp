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
    int index;
};

typedef std::vector<edge> ve;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

int n;
vi graph[MAXN];
int dist[MAXN], pointer[MAXN];

inline void add_edge(ve &edges, int from, int to, ll c, int index) {
    edge e1 = {from, to, c, 0, index};
    edge e2 = {to, from, 0, 0, -1};

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

    n += 2;

    ve edges;
    vll min_capacity(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll l, r;
        std::cin >> u >> v >> l >> r;

        min_capacity[i] = l;

        add_edge(edges, 0, v, l, i);
        add_edge(edges, u, v, r - l, i);
        add_edge(edges, u, n - 1, l, i);
    }

    dinic(edges);

    for (int to : graph[0]) {
        if (edges[to].flow < edges[to].c) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES\n";

    vll circle(m);
    for (int i = 1; i < n; i++) {
        for (int to : graph[i]) {
            edge cur_edge = edges[to];
            if (cur_edge.index != -1 && cur_edge.to != n - 1) {
                circle[cur_edge.index] = cur_edge.flow + min_capacity[cur_edge.index];
            }
        }
    }

    for (ll cur : circle) {
        std::cout << cur << '\n';
    }

    return 0;
}
