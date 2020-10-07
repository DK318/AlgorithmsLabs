#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct edge {
    int w;
    int from, to;
};

typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<edge> v_edges;
typedef std::vector<int> vi;

int find_set(vi &sets, int cur) {
    return sets[cur] == cur ? cur : sets[cur] = find_set(sets, sets[cur]);
}

void unite(vi &sets, vi &rank, int x, int y) {
    x = find_set(sets, x);
    y = find_set(sets, y);
    if (x != y) {
        if (rank[x] < rank[y]) {
            std::swap(x, y);
        }
        sets[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    vpii dots;
    vi sets(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        int x, y;
        sets[i] = i;
        std::cin >> x >> y;
        dots.push_back({x, y});
    }
    v_edges edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pii first = dots[i], second = dots[j];
            int delta_x = second.first - first.first;
            int delta_y = second.second - first.second;
            int dist = delta_x * delta_x + delta_y * delta_y;
            edges.push_back({dist, i, j});
        }
    }
    std::sort(edges.begin(), edges.end(), [](edge lhs, edge rhs) {return lhs.w < rhs.w;});
    double ans = 0;
    for (edge cur : edges) {
        int x = cur.from, y = cur.to;
        if (find_set(sets, x) != find_set(sets, y)) {
            ans += std::sqrt(cur.w);
            unite(sets, rank, x, y);
        }
    }
    std::cout << std::fixed << std::setprecision(8) << ans;
    return 0;
}
