#include <iostream>
#include <vector>

const int INF = (int) 1e9;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m;
    std::cin >> n >> m;
    vvi matrix(n, vi(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        matrix[u - 1][v - 1] = w;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << (i == j ? 0 : matrix[i][j]) << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
