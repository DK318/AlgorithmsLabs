#include <iostream>
#include <vector>
#include <map>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::map<int, int> mii;

bool kuhn(vvi &graph, vi &used, vi &mt, int cur) {
    if (used[cur]) {
        return false;
    }
    used[cur] = true;
    for (int to : graph[cur]) {
        if (mt[to] == -1 || kuhn(graph, used, mt, mt[to])) {
            mt[to] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    vvi graph(n);
    mii first, second;
    int cur1 = 0, cur2 = 0;
    for (int i = 0; i < k; i++) {
        int u, v;
        std::cin >> u >> v;
        if (first.count(u - 1) == 0) {
            first[u - 1] = cur1++;
        }
        if (second.count(v - 1) == 0) {
            second[v - 1] = cur2++;
        }
        graph[first[u - 1]].push_back(second[v - 1]);
    }
    vi mt(m, -1), used;
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        kuhn(graph, used, mt, i);
    }
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (mt[i] != -1) {
            cnt++;
        }
    }
    std::cout << cnt;
    return 0;
}
