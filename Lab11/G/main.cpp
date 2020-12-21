#include <iostream>
#include <vector>

const int INF = (int) 1e9;

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    vvi matrix(n + 1, vi(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> matrix[i][j];
        }
    }

    vi u_potential(n + 1), v_potential(n + 1), mt(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        mt[0] = i;
        int j_0 = 0;
        vi min_v_potential(n + 1, INF), used(n + 1, false);

        do {
            used[j_0] = true;

            int i_0 = mt[j_0];
            int delta = INF;
            int j_1 = 0;

            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    int cur = matrix[i_0][j] - u_potential[i_0] - v_potential[j];

                    if (cur < min_v_potential[j]) {
                        min_v_potential[j] = cur;
                        way[j] = j_0;
                    }

                    if (min_v_potential[j] < delta) {
                        delta = min_v_potential[j];
                        j_1 = j;
                    }
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u_potential[mt[j]] += delta;
                    v_potential[j] -= delta;
                } else {
                    min_v_potential[j] -= delta;
                }
            }

            j_0 = j_1;
        } while (mt[j_0] != 0);

        do {
            int j_1 = way[j_0];
            mt[j_0] = mt[j_1];
            j_0 = j_1;
        } while (j_0 > 0);
    }

    std::cout << -v_potential[0] << '\n';

    vi ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[mt[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << i << ' ' << ans[i] << '\n';
    }

    return 0;
}
