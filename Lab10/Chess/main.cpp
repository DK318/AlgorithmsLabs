#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <string>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::set<int> si;
typedef std::pair<int, int> cell;
typedef std::pair<cell, int> cell_with_color;
typedef std::pair<int, cell_with_color> node;
typedef std::vector<node> vnode;
typedef std::vector<vnode> vvnode;

int calc_type2_diag(int x, int y, int m) {
    if (x == y) {
        return 0;
    }

    if (x < y) {
        y -= x;
        return y;
    } else {
        x -= y;
        return x + m - 1;
    }
}

int calc_type1_diag(int x, int y, int m) {
    y = m - y - 1;

    if (x == y) {
        return 0;
    }

    if (x < y) {
        y -= x;
        return y;
    } else {
        x -= y;
        return x + m - 1;
    }
}

bool kuhn(vvnode &graph, vi &used, vi &mt, int cur) {
    if (used[cur]) {
        return false;
    }

    used[cur] = true;

    for (node to : graph[cur]) {
        if (mt[to.first] == -1 || kuhn(graph, used, mt, mt[to.first])) {
            mt[to.first] = cur;
            return true;
        }
    }

    return false;
}

void dfs(vvnode &graph, vi &used, int cur) {
    used[cur] = true;

    for (node to : graph[cur]) {
        if (!used[to.first]) {
            dfs(graph, used, to.first);
        }
    }
}

void min_vertex_coverage(vvnode &graph, vnode &left, vnode &right, int n) {
    vi used, mt(n, -1);

    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        kuhn(graph, used, mt, i);
    }

    vvnode graph2(2 * n);
    si left_free;

    for (int i = 0; i < n; i++) {
        for (node to : graph[i]) {
            if (mt[to.first] == i) {
                graph2[to.first + n].push_back({i, to.second});
            } else {
                graph2[i].push_back({to.first + n, to.second});
            }
        }
        left_free.insert(i);
    }

    for (int cur : mt) {
        if (cur != -1) {
            left_free.erase(cur);
        }
    }

    used.assign(2 * n, false);
    for (int cur : left_free) {
        dfs(graph2, used, cur);
    }

    for (int i = 0; i < 2 * n; i++) {
        if (i < n && !used[i]) {
            left.push_back(graph[i][0]);
        }
        if (i >= n && used[i]) {
            for (int j = 0; j < n; j++) {
                bool f = false;
                for (node cur : graph[j]) {
                    if (cur.first == i - n) {
                        right.push_back(cur);
                        f = true;
                        break;
                    }
                }
                if (f) {
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

    int n, m;
    std::cin >> n >> m;

    vvi board(n, vi(m));
    for (int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < m; j++) {
            int color = str[j];
            if (color == 'W') {
                board[i][j] = 0;
            } else {
                board[i][j] = 1;
            }
        }
    }

    vvnode graph1(m + n - 1), graph2(m + n - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int col = (i + j) % 2;
            if (board[i][j] == col) {
                graph2[calc_type2_diag(i, j, m)].push_back({calc_type1_diag(i, j, m),
                 {{i, j}, (col + 1) % 2}});
            } else {
                graph1[calc_type2_diag(i, j, m)].push_back({calc_type1_diag(i, j, m),
                 {{i, j}, col}});
            }
        }
    }

    vnode left1, left2, right1, right2;
    min_vertex_coverage(graph1, left1, right1, m + n - 1);
    min_vertex_coverage(graph2, left2, right2, m + n - 1);

    if ((left1.size() + right1.size()) > (left2.size() + right2.size())) {
        std::swap(left1, left2);
        std::swap(right1, right2);
    }

    std::cout << left1.size() + right1.size() << '\n';
    for (node cur : left1) {
        char color;
        if (cur.second.second == 0) {
            color = 'W';
        } else {
            color = 'B';
        }
        std::cout << "2 " << cur.second.first.first + 1 << ' '
        << cur.second.first.second + 1 << ' ' << color << '\n';
    }
    for (node cur : right1) {
        char color;
        if (cur.second.second == 0) {
            color = 'W';
        } else {
            color = 'B';
        }
        std::cout << "1 " << cur.second.first.first + 1 << ' '
        << cur.second.first.second + 1 << ' ' << color << '\n';
    }
    return 0;
}
