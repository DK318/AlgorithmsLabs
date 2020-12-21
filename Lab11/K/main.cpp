#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <queue>

typedef long long ll;

const ll INF = (ll) 1e18;

struct edge {
    int from, to;
    ll cap, flow;
    int index;

    edge(int from, int to, ll cap, int index) :
     from(from), to(to), cap(cap), flow(0), index(index) {}
};

typedef std::pair<ll, int> vertex;
typedef std::vector<int> vi;
typedef std::set<edge*> ve;
typedef std::vector<ve> vve;
typedef std::vector<ll> vll;
typedef std::set<vertex> sv;

void add_edge(vve &edges, vve &back_edges, int from, int to, ll cap, int index) {
    edge *e = new edge(from, to, cap, index);

    edges[from].insert(e);
    back_edges[to].insert(e);
}

void update_net(sv &sorted_vertices, vll &p_in, vll &p_out, vll &p, edge *e, ll sub) {
    p_in[e->to] -= sub;
    p_out[e->from] -= sub;

    sorted_vertices.erase(sorted_vertices.find({p[e->from], e->from}));
    sorted_vertices.erase(sorted_vertices.find({p[e->to], e->to}));

    p[e->from] = std::min(p_in[e->from], p_out[e->from]);
    p[e->to] = std::min(p_in[e->to], p_out[e->to]);

    sorted_vertices.insert({p[e->from], e->from});
    sorted_vertices.insert({p[e->to], e->to});
}

void delete_vertex(vve &edges, vve &back_edges, sv &sorted_vertices, vll &p_in,
 vll &p_out, vll &p, vertex cur_vertex) {
    for (edge *cur_edge : edges[cur_vertex.second]) {
        update_net(sorted_vertices, p_in, p_out, p, cur_edge, cur_edge->cap - cur_edge->flow);
        back_edges[cur_edge->to].erase(cur_edge);
    }

    for (edge *cur_edge : back_edges[cur_vertex.second]) {
        update_net(sorted_vertices, p_in, p_out, p, cur_edge, cur_edge->cap - cur_edge->flow);
        edges[cur_edge->from].erase(cur_edge);
    }

    sorted_vertices.erase(cur_vertex);
}

void bfs_t(vve &edges, sv &sorted_vertices, vll &p_in, vll &p_out,
 vll &p, vll &result, int n, vertex start_vertex) {
    std::queue<int> q;
    q.push(start_vertex.second);

    vll vertex_flow(n, 0);
    vertex_flow[start_vertex.second] = start_vertex.first;

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();

        ll cur_flow = vertex_flow[cur_vertex];

        for (edge *cur_edge : edges[cur_vertex]) {
            ll delta = std::min(cur_flow, cur_edge->cap - cur_edge->flow);
            if (delta != 0) {
                cur_flow -= delta;
                cur_edge->flow += delta;
                result[cur_edge->index] += delta;
                update_net(sorted_vertices, p_in, p_out, p, cur_edge, delta);
                vertex_flow[cur_edge->to] += delta;
                q.push(cur_edge->to);
            }
        }
    }
}

void bfs_s(vve &back_edges, sv &sorted_vertices, vll &p_in, vll &p_out,
 vll &p, vll &result, int n, vertex start_vertex) {
    std::queue<int> q;
    q.push(start_vertex.second);

    vll vertex_flow(n, 0);
    vertex_flow[start_vertex.second] = start_vertex.first;

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();

        ll cur_flow = vertex_flow[cur_vertex];

        for (edge *cur_edge : back_edges[cur_vertex]) {
            ll delta = std::min(cur_flow, cur_edge->cap - cur_edge->flow);
            if (delta != 0) {
                cur_flow -= delta;
                cur_edge->flow += delta;
                result[cur_edge->index] += delta;
                update_net(sorted_vertices, p_in, p_out, p, cur_edge, delta);
                vertex_flow[cur_edge->from] += delta;
                q.push(cur_edge->from);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, l;
    std::cin >> n >> m >> l;

    vi layers(n);
    int s = 0, t = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> layers[i];

        if (layers[i] == 1) {
            s = i;
        }

        if (layers[i] == l) {
            t = i;
        }

        layers[i]--;
    }

    vll p_in(n), p_out(n);
    p_in[s] = INF;
    p_out[t] = INF;

    vve edges(n), back_edges(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        std::cin >> u >> v >> c;

        add_edge(edges, back_edges, u - 1, v - 1, c, i);
        p_in[v - 1] += c;
        p_out[u - 1] += c;
    }

    vll p(n);
    sv sorted_vertices;
    for (int i = 0; i < n; i++) {
        p[i] = std::min(p_in[i], p_out[i]);
        sorted_vertices.insert({p[i], i});
    }

    vll result(m, 0);
    while (!sorted_vertices.empty()) {
        vertex cur_vertex = *(sorted_vertices.begin());

        if (cur_vertex.first == 0) {
            delete_vertex(edges, back_edges, sorted_vertices,
             p_in, p_out, p, cur_vertex);
        } else {
            bfs_t(edges, sorted_vertices, p_in, p_out,
             p, result, n, cur_vertex);
            bfs_s(back_edges, sorted_vertices, p_in, p_out,
             p, result, n, cur_vertex);
        }
    }

    for (ll cur : result) {
        std::cout << cur << '\n';
    }

    return 0;
}
