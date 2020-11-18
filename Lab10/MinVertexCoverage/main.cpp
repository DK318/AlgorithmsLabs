#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::map<int, int> mii;
typedef std::set<int> set;

void dfs(vvi &graph, vi &used, int cur) {
    used[cur] = true;
    for (int to : graph[cur]) {
        if (!used[to]) {
            dfs(graph, used, to);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int m, n;
    std::cin >> m >> n;
    vvi graph(m);
    mii left_map, right_map, left_map_tr, right_map_tr;
    set left;
    int cur = 0;
    for (int i = 0; i < m; i++) {
        int k;
        std::cin >> k;
        left.insert(cur);
        left_map[i] = cur++;
        left_map_tr[cur - 1] = i;
        for (int j = 0; j < k; j++) {
            int u;
            std::cin >> u;
            if (right_map.count(u - 1) == 0) {
                right_map[u - 1] = cur++;
                right_map_tr[cur - 1] = u - 1;
            }
            graph[i].push_back(u - 1);
        }
    }
    vi mt(m);
    set free_vertices;
    for (int i = 0; i < m; i++) {
        std::cin >> mt[i];
        mt[i]--;
        if (mt[i] == -1) {
            free_vertices.insert(left_map[i]);
        }
    }
    vvi graph2(m + n);
    for (int i = 0; i < m; i++) {
        for (int to : graph[i]) {
            if (mt[i] == to) {
                graph2[right_map[to]].push_back(left_map[i]);
            } else {
                graph2[left_map[i]].push_back(right_map[to]);
            }
        }
    }
    vi used(n + m, false);
    for (auto it = free_vertices.begin(); it != free_vertices.end(); it++) {
        int cur = *it;
        if (!used[cur]) {
            dfs(graph2, used, cur);
        }
    }
    vi first, second;
    for (int i = 0; i < m + n; i++) {
        if (!used[i] && left.count(i) == 1) {
            first.push_back(left_map_tr[i] + 1);
        }
        if (used[i] && left.count(i) == 0) {
            second.push_back(right_map_tr[i] + 1);
        }
    }
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());
    std::cout << first.size() + second.size() << '\n';
    std::cout << first.size() << ' ';
    for (int cur : first) {
        std::cout << cur << ' ';
    }
    std::cout << '\n' << second.size() << ' ';
    for (int cur : second) {
        std::cout << cur << ' ';
    }
    return 0;
}
