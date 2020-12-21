#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>

typedef long long ll;

const ll INF = (ll) 1e18;
const int MAXN = 3000;

struct edge {
    int from, to, index;
    ll c, flow, cost;
    int result_index;
};

typedef std::vector<edge> ve;
typedef std::vector<edge*> vptre;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<ll, ll> pllll;
typedef std::pair<pllll, pllll> task;
typedef std::vector<task> vtask;

int n;
vi graph[MAXN];
std::vector<ll> dist;

inline void add_edge(ve &edges, int from, int to, ll c, ll cost, int index) {
    edge e1 = {from, to, (int) edges.size(), c, 0, cost, index};
    edge e2 = {to, from, (int) edges.size() + 1, 0, 0, -cost, index};

    graph[from].push_back(e1.index);
    edges.push_back(e1);
    graph[to].push_back(e2.index);
    edges.push_back(e2);
}

inline bool bfs(ve &edges, vptre &parent) {
    std::queue<int> q;
    q.push(0);

    dist.assign(2 * n + 3, INF);

    dist[0] = 0;

    int t = 2 * n + 2;
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

    vptre parent(2 * n + 3);
    while (bfs(edges, parent)) {
        std::pair<ll, ll> cur_flow = dfs(edges, parent, 2 * n + 2, INF);
        max_flow += cur_flow.first;
    }

    return max_flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int k;
    std::cin >> n >> k;

    ve edges;
    vtask tasks(n);
    for (int i = 0; i < n; i++) {
        ll s, t, c;
        std::cin >> s >> t >> c;

        tasks[i] = {{s, t + s}, {c, i}};
    }

    std::sort(tasks.begin(), tasks.end());
    for (int i = 0; i < n; i++) {
        add_edge(edges, i + 2, i + n + 2, 1, -tasks[i].second.first, (int) tasks[i].second.second);
        add_edge(edges, 1, i + 2, k, 0, -1);
        add_edge(edges, i + n + 2, 2 * n + 2, 1, 0, -1);
    }

    add_edge(edges, 0, 1, k, 0, -1);

    for (int i = 0; i < n - 1; i++) {
        add_edge(edges, i + 2, i + 3, k, 0, -1);
        for (int j = i + 1; j < n; j++) {
            if (tasks[j].first.first >= tasks[i].first.second) {
                add_edge(edges, i + n + 2, j + 2, 1, 0, -1);
                break;
            }
        }
    }

    dinic(edges);

    vi result(n, 0);
    for (edge &e : edges) {
        if (e.result_index != -1 && e.flow == 1) {
            result[e.result_index] = 1;
        }
    }

    for (int cur : result) {
        std::cout << cur << ' ';
    }

    return 0;
}
