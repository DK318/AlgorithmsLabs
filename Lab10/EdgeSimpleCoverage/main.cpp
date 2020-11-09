#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cstdlib>
#include <stack>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;
typedef std::multiset<pii> mspii;
typedef std::set<pii> spii;

void euler(vvi &graph, mspii &edges, vi &deg, vi &path, int start) {
    std::stack<int> stack;
    stack.push(start);
    while (!stack.empty()) {
        int cur = stack.top();
        if (deg[cur] == 0) {
            path.push_back(cur);
            stack.pop();
        } else {
            for (int to : graph[cur]) {
                pii edge = {cur, to};
                if (edge.first > edge.second) {
                    std::swap(edge.first, edge.second);
                }
                if (edges.count(edge) != 0) {
                    edges.erase(edges.find(edge));
                    deg[cur]--;
                    deg[to]--;
                    stack.push(to);
                    break;
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m;
    std::cin >> n >> m;
    vvi graph(n);
    mspii edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u > v) {
            std::swap(u, v);
        }
        edges.insert({u - 1, v - 1});
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    vi odd_vertices, deg(n);
    for (int i = 0; i < n; i++) {
        deg[i] = (int) graph[i].size();
        if ((graph[i].size() & 1) != 0) {
            odd_vertices.push_back(i);
        }
    }
    spii added_edges;
    for (size_t i = 0; i < odd_vertices.size(); i += 2) {
        int u = odd_vertices[i], v = odd_vertices[i + 1];
        if (u > v) {
            std::swap(u, v);
        }
        added_edges.insert({u, v});
        edges.insert({u, v});
        deg[u]++;
        deg[v]++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vi path;
    int start = 0;
    if (!odd_vertices.empty()) {
        start = odd_vertices[0];
    }
    euler(graph, edges, deg, path, start);
    if (odd_vertices.empty()) {
        std::cout << "1\n";
        for (int cur : path) {
            std::cout << cur + 1 << ' ';
        }
        return 0;
    }
    vvi paths;
    vi cur_path;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i], v = path[i + 1];
        cur_path.push_back(u);
        if (u > v) {
            std::swap(u, v);
        }
        if (added_edges.count({u, v}) != 0) {
            if (cur_path.size() > 1) {
                paths.push_back(cur_path);
            }
            cur_path.clear();
            added_edges.erase({u, v});
        }
    }
    if (!cur_path.empty()) {
        cur_path.push_back(path.back());
        paths.push_back(cur_path);
    }
    size_t min_path_cnt = odd_vertices.size() / 2;
    if (paths.size() != min_path_cnt) {
        vi path1 = paths[0], path2 = paths.back();
        paths.pop_back();
        std::swap(paths[0], paths[paths.size() - 1]);
        paths.pop_back();
        vi new_path;
        for (size_t i = 0; i < path2.size() - 1; i++) {
            new_path.push_back(path2[i]);
        }
        for (int c : path1) {
            new_path.push_back(c);
        }
        paths.push_back(new_path);
    }
    std::cout << min_path_cnt << '\n';
    for (auto &p : paths) {
        for (int cur : p) {
            std::cout << cur + 1 << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
