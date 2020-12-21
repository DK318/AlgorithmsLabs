#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool kuhn(vvi &graph, vi &mt, vi &used, int cur, int min_weight) {
    if (used[cur]) {
        return false;
    }

    used[cur] = true;
    for (size_t i = 0; i < graph[cur].size(); i++) {
        if (graph[cur][i] < min_weight) {
            continue;
        }

        if (mt[i] == -1 || kuhn(graph, mt, used, mt[i], min_weight)) {
            mt[i] = cur;
            return true;
        }
    }

    return false;
}

void build_matching(vvi &graph, vi &mt, int min_weight) {
    vi used;
    for (size_t i = 0; i < graph.size(); i++) {
        used.assign(graph.size(), false);
        kuhn(graph, mt, used, i, min_weight);
    }
}

bool check_matching(vi &mt) {
    for (size_t i = 0; i < mt.size(); i++) {
        if (mt[i] == -1) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    vvi graph(n, vi(n));
    vi weights;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c;
            std::cin >> c;

            graph[i][j] = c;
            weights.push_back(c);
        }
    }

    std::sort(weights.begin(), weights.end());
    int l = -1, r = (int) weights.size();
    while (l < r - 1) {
        int mid = (l + r) / 2;

        vi mt(n, -1);
        build_matching(graph, mt, weights[mid]);

        if (check_matching(mt)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    if (r == (int) weights.size()) {
        std::cout << weights[r - 1];
    } else {
        vi mt(n, -1);
        build_matching(graph, mt, weights[r]);
        if (check_matching(mt)) {
            std::cout << weights[r];
        } else {
            std::cout << weights[l];
        }
    }

    return 0;
}
