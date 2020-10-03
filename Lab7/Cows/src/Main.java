import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), m = scanner.nextInt();
        DSU dsu = new DSU(n);
        for (int i = 1; i <= m; i++) {
            int u = scanner.nextInt() - 1, v = scanner.nextInt() - 1;
            String var = scanner.next();
            if (var.equals("T")) {
                dsu.unite(u, v);
                dsu.unite(u + n, v + n);
            } else {
                dsu.unite(u + n, v);
                dsu.unite(u, v + n);
            }
            if ((dsu.findSet(u) == dsu.findSet(u + n)) || (dsu.findSet(v) == dsu.findSet(v + n))) {
                System.out.println(i - 1);
                return;
            }
        }
        System.out.println(m);
    }
}

class DSU {
    private ArrayList<Integer> parents, rank;

    public DSU(int n) {
        parents = new ArrayList<>();
        rank = new ArrayList<>();
        for (int i = 0; i < 2 * n; i++) {
            parents.add(i);
            rank.add(0);
        }
    }

    public int findSet(int x) {
        if (x == parents.get(x)) {
            return x;
        } else {
            parents.set(x, findSet(parents.get(x)));
            return parents.get(x);
        }
    }

    public void unite(int x, int y) {
        x = findSet(x);
        y = findSet(y);
        if (x != y) {
            if (rank.get(x) < rank.get(y)) {
                int tmp = x;
                x = y;
                y = tmp;
            }
            parents.set(y, x);
            if (rank.get(x).equals(rank.get(y))) {
                rank.set(x, rank.get(x) + 1);
            }
        }
    }
}

class Scanner {
    private BufferedReader reader;
    private StringTokenizer tokenizer;

    public Scanner(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }
}