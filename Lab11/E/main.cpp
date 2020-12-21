#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <set>

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
typedef std::set<edge> se;
typedef std::pair<int, edge> pie;
typedef std::vector<pie> vpie;
typedef std::pair<ll, vpie> pllvpie;
typedef std::vector<pllvpie> vpllvpie;
typedef std::set<int> si;

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

void simple_decomposition(ve &edges, pllvpie &dec, int cur) {
    si p;
    vpie q;

    int v = cur;
    while (p.count(v) == 0) {
        if (v == n - 1) {
            break;
        }

        edge e;
        int index = -1;
        for (int to : graph[v]) {
            edge cur_edge = edges[to];
            if (cur_edge.flow > 0) {
                e = cur_edge;
                index = to;
                break;
            }
        }

        if (index == -1) {
            dec.second.clear();
            return;
        }

        q.push_back({index, e});
        p.insert(v);
        v = e.to;
    }

    if (p.count(v) == 1) {
        while (q.begin()->second.from != v) {
            q.erase(q.begin());
        }
    }

    ll min_flow = INF;
    for (pie &cur_edge : q) {
        min_flow = std::min(min_flow, cur_edge.second.flow);
    }

    for (size_t i = 0; i < q.size(); i++) {
        q[i].second.flow -= min_flow;
        int index = q[i].first;
        edges[index].flow -= min_flow;
    }

    dec = {min_flow, q};
}

void full_decomposition(ve &edges, vpllvpie &full_dec) {
    pllvpie p;
    simple_decomposition(edges, p, 0);

    while (!p.second.empty()) {
        full_dec.push_back(p);
        simple_decomposition(edges, p, 0);
    }

    for (int i = 1; i < n; i++) {
        simple_decomposition(edges, p, i);
        while (!p.second.empty()) {
            full_dec.push_back(p);
            simple_decomposition(edges, p, i);
        }
    }
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
    }

    dinic(edges);

    ve edges_copy = edges;
    vpllvpie decomposition;
    full_decomposition(edges, decomposition);

    std::cout << decomposition.size() << '\n';
    for (pllvpie &cur : decomposition) {
        std::cout << cur.first << ' ' << cur.second.size() << ' ';
        for (pie &e : cur.second) {
            std::cout << (e.first / 2) + 1 << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
