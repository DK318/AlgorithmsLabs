import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[][] matrix = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = scanner.nextInt();
            }
        }
        Solver solver = new Solver(n, matrix);
        System.out.println(solver.solve());
    }
}

class Solver {
    private int n;
    private int[][] matrix;
    private ArrayList<ArrayList<Integer>> graph, graphTr;
    private ArrayList<Boolean> used;
    private ArrayList<Integer> order, component;

    private void assignUsed() {
        used = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            used.add(false);
        }
    }

    public Solver(int n, int[][] matrix) {
        this.n = n;
        this.matrix = matrix;
    }

    private void dfs1(int cur) {
        used.set(cur, true);
        for (int to : graph.get(cur)) {
            if (!used.get(to)) {
                dfs1(to);
            }
        }
        order.add(cur);
    }

    private void dfs2(int cur) {
        used.set(cur, true);
        component.add(cur);
        for (int to : graphTr.get(cur)) {
            if (!used.get(to)) {
                dfs2(to);
            }
        }
    }

    private boolean tryCondensate() {
        order = new ArrayList<>();
        component = new ArrayList<>();
        assignUsed();
        for (int i = 0; i < n; i++) {
            if (!used.get(i)) {
                dfs1(i);
            }
        }
        assignUsed();
        dfs2(order.get(n - 1));
        return component.size() == n;
    }

    private void makeGraph(int d) {
        graph = new ArrayList<>();
        graphTr = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
            graphTr.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && matrix[i][j] <= d) {
                    graph.get(i).add(j);
                    graphTr.get(j).add(i);
                }
            }
        }
    }

    public int solve() {
        int l = 0, r = (int) 1e9 + 1;
        while (l + 2 < r) {
            int mid = (l + r) / 2;
            makeGraph(mid);
            if (tryCondensate()) {
                r = mid + 1;
            } else {
                l = mid + 1;
            }
        }
        makeGraph(l);
        if (tryCondensate()) {
            return l;
        } else {
            return l + 1;
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