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
typedef std::vector<ll> vll;
typedef std::vector<vll> vvll;

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

    dist.assign(2 * n + 2, INF);

    dist[0] = 0;

    int t = 2 * n + 1;
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

    vptre parent(2 * n + 2);
    while (bfs(edges, parent)) {
        std::pair<ll, ll> cur_flow = dfs(edges, parent, 2 * n + 1, INF);
        max_flow += cur_flow.second;
    }

    return max_flow;
}

void hungarian_algorithm(vvll &matrix, vll &result) {
    vll u_potential(n + 1), v_potential(n + 1), mt(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        mt[0] = i;
        ll j_0 = 0;
        vll min_v_potential(n + 1, INF), used(n + 1, false);

        do {
            used[(size_t)j_0] = true;

            ll i_0 = mt[(size_t)j_0];
            ll delta = INF;
            ll j_1 = 0;

            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    ll cur = matrix[(size_t)i_0][j] - u_potential[(size_t)i_0] - v_potential[j];

                    if (cur < min_v_potential[j]) {
                        min_v_potential[j] = cur;
                        way[j] = j_0;
                    }

                    if (min_v_potential[j] < delta) {
                        delta = min_v_potential[j];
                        j_1 = j;
                    }
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u_potential[(size_t)mt[j]] += delta;
                    v_potential[j] -= delta;
                } else {
                    min_v_potential[j] -= delta;
                }
            }

            j_0 = j_1;
        } while (mt[(size_t)j_0] != 0);

        do {
            ll j_1 = way[(size_t)j_0];
            mt[(size_t)j_0] = mt[(size_t)j_1];
            j_0 = j_1;
        } while (j_0 > 0);
    }

    for (int i = 1; i <= n; i++) {
        result[(size_t)mt[i]] = i;
        matrix[(size_t)mt[i]][i] = INF;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int k;
    std::cin >> n >> k;

    ve edges;
    vvll matrix(n + 1, vll(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ll cost;
            std::cin >> cost;

            matrix[i][j] = cost;
            add_edge(edges, i, j + n, 1, cost);
        }
    }

    for (int i = 1; i <= n; i++) {
        add_edge(edges, 0, i, k, 0);
        add_edge(edges, i + n, 2 * n + 1, k, 0);
    }

    std::cout << dinic(edges) << '\n';

    for (int i = 1; i <= n; i++) {
        for (int to : graph[i]) {
            edge cur_edge = edges[to];
            if (cur_edge.c == 1 && cur_edge.flow == 0) {
                matrix[cur_edge.from][cur_edge.to - n] = INF;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        vll result(n + 1);
        hungarian_algorithm(matrix, result);

        for (int j = 1; j <= n; j++) {
            std::cout << result[j] << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}
