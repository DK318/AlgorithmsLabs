import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        int n, m;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            u = scanner.nextInt();
            v = scanner.nextInt();
            graph.get(u - 1).add(v - 1);
            graph.get(v - 1).add(u - 1);
        }
        Solver solver = new Solver(n, m, graph);
        Pair<Integer, ArrayList<Integer>> ans = solver.solve();
        System.out.println(ans.first);
        for (int cur : ans.second) {
            System.out.print(cur + " ");
        }
    }
}

class Solver {
    private int n, m, timer = 0, maxColor = 0;
    private ArrayList<ArrayList<Integer>> graph;
    private ArrayList<Boolean> used;
    private ArrayList<Integer> tin, up, colors;

    public Solver(int n, int m, ArrayList<ArrayList<Integer>> graph) {
        this.n = n;
        this.m = m;
        this.graph = graph;
    }

    private void makeTinAndUp(int cur, int from) {
        used.set(cur, true);
        timer++;
        tin.set(cur, timer);
        up.set(cur, timer);
        for (int to : graph.get(cur)) {
            if (to == from) {
                continue;
            }
            if (used.get(to)) {
                up.set(cur, Math.min(up.get(cur), tin.get(to)));
            } else {
                makeTinAndUp(to, cur);
                up.set(cur, Math.min(up.get(cur), up.get(to)));
            }
        }
    }

    private void makeTinAndUp() {
        used = new ArrayList<>();
        tin = new ArrayList<>();
        up = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            used.add(false);
            tin.add(0);
            up.add(0);
        }
        for (int i = 0; i < n; i++) {
            if (!used.get(i)) {
                makeTinAndUp(i, -1);
            }
        }
    }

    private void paint(int cur, int color) {
        colors.set(cur, color);
        for (int to : graph.get(cur)) {
            if (colors.get(to) == 0) {
                if (up.get(to) > tin.get(cur)) {
                    maxColor++;
                    paint(to, maxColor);
                } else {
                    paint(to, color);
                }
            }
        }
    }

    public Pair<Integer, ArrayList<Integer>> solve() {
        makeTinAndUp();
        colors = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            colors.add(0);
        }
        for (int i = 0; i < n; i++) {
            if (colors.get(i) == 0) {
                maxColor++;
                paint(i, maxColor);
            }
        }
        return new Pair<>(maxColor, colors);
    }
}

class Pair<U, V> {
    public U first;
    public V second;

    public Pair(U first, V second) {
        this.first = first;
        this.second = second;
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