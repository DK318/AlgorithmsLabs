#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <utility>
#include <stack>
#include <cstdlib>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;
typedef std::multiset<pii> mspii;

void make_graph(vvi &graph, int d, int k) {
    int n = (int) (std::pow(d, k) + 0.5);

    graph.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            graph[i].push_back((i * d + j) % n);
        }
    }
}

void euler(vvi &graph, vi &path, int start) {
    std::stack<int> stack;
    vi used(graph.size(), false);
    stack.push(start);
    while (!stack.empty()) {
        int cur = stack.top();
        used[cur] = true;
        if (graph[cur].size() == 0) {
            path.push_back(cur);
            stack.pop();
        } else {
            int to = graph[cur].back();
            graph[cur].pop_back();
            if (!used[to]) {
                stack.push(to);
            }
        }
    }
    std::reverse(path.begin(), path.end());
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int d, k;
    std::cin >> d >> k;

    vvi graph;
    make_graph(graph, d, k);

    vi path;
    euler(graph, path, 0);

    for (int i = 0; i < k - 1; i++) {
        std::cout << 0;
    }

    for (int cur : path) {
        std::cout << cur % d;
    }

    return 0;
}
