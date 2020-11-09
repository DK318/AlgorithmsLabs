#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool kuhn(vvi &graph, vi &used, vi &mt, int &cnt, int cur) {
    if (used[cur]) {
        return false;
    }
    used[cur] = true;
    for (int to : graph[cur]) {
        if (mt[to] == -1 || kuhn(graph, used, mt, cnt, mt[to])) {
            if (mt[to] == -1) {
                cnt--;
            }
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
    int n, m;
    std::cin >> n >> m;
    vvi graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }
    vi mt(n, -1), used;
    int cnt = n;
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        kuhn(graph, used, mt, cnt, i);
    }
    std::cout << cnt;
    return 0;
}
