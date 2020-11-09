#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <stack>
 
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;
typedef std::multiset<pii> mspii;
 
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
    int n;
    mspii edges;
    std::cin >> n;
    vvi graph(n);
    vi deg(n);
    int cnt_odd = 0, start = 0;
    for (int i = 0; i < n; i++) {
        int m;
        std::cin >> m;
        deg[i] = m;
        if ((m & 1) != 0) {
            cnt_odd++;
            start = i;
        }
        for (int j = 0; j < m; j++) {
            int to;
            std::cin >> to;
            if (to > i) {
                pii edge = {i, to - 1};
                if (edge.first > edge.second) {
                    std::swap(edge.first, edge.second);
                }
                edges.insert(edge);
            }
            graph[i].push_back(to - 1);
        }
    }
    if (cnt_odd > 2) {
        std::cout << -1;
        return 0;
    }
    vi path;
    euler(graph, edges, deg, path, start);
    std::cout << path.size() - 1 << '\n';
    for (int cur : path) {
        std::cout << cur + 1 << ' ';
    }
    return 0;
}