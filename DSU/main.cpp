#include <bits/stdc++.h>

using namespace std;

vector<int> p;

void build(int n) {
    for (int i = 0; i <= n; i++) {
        p.push_back(i);
    }
}

int find(int v) {
    return p[v] == v ? v : p[v] = find(p[v]);
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) {
        return;
    }
    if (rand() % 2) {
        p[u] = v;
    } else {
        p[v] = u;
    }
}

int main() {
    srand(time(0));
    int n; cin >> n;
    build(n);
    while (true) {
        int type; cin >> type;
        if (type == 3) {
            break;
        }
        if (type == 1) {
            int q; cin >> q;
            cout << find(q) << '\n';
        }
        if (type == 2) {
            int u, v; cin >> u >> v;
            unite(u, v);
        }
    }
    return 0;
}
