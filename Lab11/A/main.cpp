#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool kuhn(vvi &graph, vi &used, vi &mt, vi &mt_tr, int n_l, int cur) {
    if (used[cur]) {
        return false;
    }

    used[cur] = true;

    for (int to : graph[cur]) {
        to -= n_l;
        if (mt[to] == -1 || kuhn(graph, used, mt, mt_tr, n_l, mt[to])) {
            mt[to] = cur;
            mt_tr[cur] = to;
            return true;
        }
    }

    return false;
}

void dfs(vvi &graph, vi &mt, vi &used, int n_l, int cur) {
    used[cur - n_l] = true;
    for (int to : graph[cur]) {
        if (!used[mt[to]]) {
            dfs(graph, mt, used, n_l, mt[to] + n_l);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n_l, n_r;
    while (std::cin >> n_l >> n_r) {
        int m;
        std::cin >> m;

        vvi graph(n_l + n_r);
        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            graph[u - 1].push_back(v - 1 + n_l);
            graph[v - 1 + n_l].push_back(u - 1);
        }

        vi used, mt(n_r, -1), mt_tr(n_l, -1);

        for (int run = 1; run != 0;) {
            run = 0;
            used.assign(n_l, false);

            for (int i = 0; i < n_l; i++) {
                if (mt_tr[i] == -1 && kuhn(graph, used, mt, mt_tr, n_l, i)) {
                    run = 1;
                }
            }
        }

        int start = -1;
        for (int i = 0; i < n_r; i++) {
            if (mt[i] == -1) {
                start = i + n_l;
                break;
            }
        }

        if (start == -1) {
            std::cout << "0\n\n";
            continue;
        }

        used.assign(n_r, false);
        dfs(graph, mt_tr, used, n_l, start);

        vi res;
        for (int i = 0; i < n_r; i++) {
            if (used[i]) {
                res.push_back(i + 1);
            }
        }

        std::cout << res.size() << '\n';

        for (int cur : res) {
            std::cout << cur << ' ';
        }

        std::cout << "\n\n";
    }

    return 0;
}
