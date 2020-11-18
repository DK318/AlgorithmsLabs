#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

void dfs(vvi &graph, vi &mt, vi &used, int cur) {
    for (int to : graph[cur]) {
        if (used[to] == 0) {
            used[to] = 1;
            dfs(graph, mt, used, mt[to]);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    vvi graph(n);
    for (int i = 0; i < n; i++) {
        int k;
        std::cin >> k;

        for (int j = 0; j < k; j++) {
            int u;
            std::cin >> u;
            graph[i].push_back(u - 1);
        }
    }

    vi mt(n), mt_tr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> mt[i];
        mt[i]--;
        mt_tr[mt[i]] = i;
    }

    vvi reachable(n, vi(n, 0));
    for (int i = 0; i < n; i++) {
        dfs(graph, mt_tr, reachable[i], i);
    }

    vvi ans(n);
    for (int i = 0; i < n; i++) {
        ans[i].push_back(mt[i] + 1);

        for (int to : graph[i]) {
            if (mt[i] == to) {
                continue;
            }

            int left = mt_tr[to];
            int right = mt[i];

            if (reachable[left][right] == 1) {
                ans[i].push_back(to + 1);
            }
        }
    }

    for (vi &cur : ans) {
        std::cout << cur.size() << ' ';

        for (int right : cur) {
            std::cout << right << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
