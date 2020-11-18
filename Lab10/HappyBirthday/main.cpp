#include <iostream>
#include <vector>
#include <set>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::set<int> si;

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

    int k;
    std::cin >> k;

    while (k--) {
        int m, n;
        std::cin >> m >> n;

        vvi graph(m);
        for (int i = 0; i < m; i++) {
            int cur;
            si right;
            std::cin >> cur;
            while (cur != 0) {
                right.insert(cur - 1);
                std::cin >> cur;
            }
            for (int j = 0; j < n; j++) {
                if (right.count(j) == 0) {
                    graph[i].push_back(j);
                }
            }
        }

        vi mt(n, -1), used;
        for (int i = 0; i < m; i++) {
            used.assign(m, false);
            kuhn(graph, used, mt, i);
        }

        vvi graph2(n + m);
        si left_free;

        for (int i = 0; i < m; i++) {
            for (int cur : graph[i]) {
                if (mt[cur] == i) {
                    graph2[cur + m].push_back(i);
                } else {
                    graph2[i].push_back(cur + m);
                }
            }
            left_free.insert(i);
        }

        for (int cur : mt) {
            if (cur != -1) {
                left_free.erase(cur);
            }
        }

        used.assign(n + m, false);
        for (int cur : left_free) {
            dfs(graph2, used, cur);
        }

        vi left_ans, right_ans;
        for (int i = 0; i < n + m; i++) {
            if (i < m && used[i]) {
                left_ans.push_back(i + 1);
            } else if (i >= m && !used[i]) {
                right_ans.push_back(i - m + 1);
            }
        }

        std::cout << left_ans.size() + right_ans.size() << '\n';
        std::cout << left_ans.size() << ' ' << right_ans.size() << '\n';
        for (int cur : left_ans) {
            std::cout << cur << ' ';
        }
        std::cout << '\n';
        for (int cur : right_ans) {
            std::cout << cur << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
