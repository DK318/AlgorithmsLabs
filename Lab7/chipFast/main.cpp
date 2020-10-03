#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::pair<int, bool> pib;
typedef std::vector<pib> vpib;
typedef std::vector<vi> vvi;

int not_var(int var, int n) {
    return var >= n ? var - n : var + n;
}

void add_edges(vvi &graph, vvi &graph_tr, int n, int a, int b) {
    int not_a = not_var(a, n);
    int not_b = not_var(b, n);
    graph[a].push_back(not_b);
    graph[b].push_back(not_a);
    graph_tr[not_a].push_back(b);
    graph_tr[not_b].push_back(a);
}

void dfs1(vvi &graph, vi &used, vi &order, int cur) {
    used[cur] = true;
    for (int to : graph[cur]) {
        if (!used[to]) {
            dfs1(graph, used, order, to);
        }
    }
    order.push_back(cur);
}

void dfs2(vvi &graph_tr, vi &used, vi &comps, int cur, int color) {
    used[cur] = true;
    comps[cur] = color;
    for (int to : graph_tr[cur]) {
        if (!used[to]) {
            dfs2(graph_tr, used, comps, to, color);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    vi colors(n);
    for (int i = 0; i < n; i++) {
        std::cin >> colors[i];
    }
    vvi position(n);
    vpib wires(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        int x;
        std::cin >> x;
        wires[i] = {x - 1, position[x - 1].size() == 1};
        position[x - 1].push_back(i);
    }
    vvi graph(2 * n), graph_tr(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        int first = i, second = (i + 1) % (2 * n);
        int a = wires[first].first, b = wires[second].first;
        if (colors[a] == colors[b]) {
            if (wires[first].second) {
                a = not_var(a, n);
            }
            if (wires[second].second) {
                b = not_var(b, n);
            }
            add_edges(graph, graph_tr, n, a, b);
        }
    }
    vi order, comps(2 * n), used(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i]) {
            dfs1(graph, used, order, i);
        }
    }
    used.assign(2 * n, false);
    std::reverse(order.begin(), order.end());
    int color = 0;
    for (int i : order) {
        if (!used[i]) {
            dfs2(graph_tr, used, comps, i, color);
            color++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (comps[i] == comps[not_var(i, n)]) {
            std::cout << "NO";
            return 0;
        }
    }
    vi ans;
    for (int i = 0; i < n; i++) {
        if (comps[i] > comps[not_var(i, n)]) {
            ans.push_back(position[i][0] + 1);
        } else {
            ans.push_back(position[i][1] + 1);
        }
    }
    std::cout << "YES\n";
    for (int cur : ans) {
        std::cout << cur << ' ';
    }
    return 0;
}
