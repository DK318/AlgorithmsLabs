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
        ArrayList<ArrayList<Pair<Integer, Integer>>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            u = scanner.nextInt();
            v = scanner.nextInt();
            graph.get(u - 1).add(new Pair<>(v - 1, i));
            graph.get(v - 1).add(new Pair<>(u - 1, i));
        }
        Solver solver = new Solver(n, m, graph);
        Pair<Integer, ArrayList<Integer>> ans = solver.solve();
        System.out.println(ans.first);
        for (Integer cur : ans.second) {
            System.out.print(cur + " ");
        }
    }
}

class Solver {
    private int n;
    private int m;
    private ArrayList<ArrayList<Pair<Integer, Integer>>> graph;
    private ArrayList<Boolean> used;
    private ArrayList<Integer> tin, up, colors;
    private int maxColor = 0;
    private int timer = 0;

    public Solver(int n, int m, ArrayList<ArrayList<Pair<Integer, Integer>>> graph) {
        this.n = n;
        this.m = m;
        this.graph = graph;
    }

    private void makeTinAndUp(int cur, int from) {
        timer++;
        up.set(cur, timer);
        tin.set(cur, timer);
        used.set(cur, true);
        for (Pair<Integer, Integer> to : graph.get(cur)) {
            if (to.first == from) {
                continue;
            }
            if (used.get(to.first)) {
                up.set(cur, Math.min(up.get(cur), tin.get(to.first)));
            } else {
                makeTinAndUp(to.first, cur);
                up.set(cur, Math.min(up.get(to.first), up.get(cur)));
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

    private void paint(int cur, int color, int from) {
        used.set(cur, true);
        for (Pair<Integer, Integer> to : graph.get(cur)) {
            if (to.first == from) {
                continue;
            }
            if (!used.get(to.first)) {
                if (up.get(to.first) >= tin.get(cur)) {
                    maxColor++;
                    colors.set(to.second, maxColor);
                    paint(to.first, maxColor, cur);
                } else {
                    colors.set(to.second, color);
                    paint(to.first, color, cur);
                }
            } else if (tin.get(to.first) < tin.get(cur)) {
                colors.set(to.second, color);
            }
        }
    }

    public Pair<Integer, ArrayList<Integer>> solve() {
        makeTinAndUp();
        for (int i = 0; i < n; i++) {
            used.set(i, false);
        }
        colors = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            colors.add(0);
        }
        for (int i = 0; i < n; i++) {
            if (!used.get(i)) {
                paint(i, maxColor, -1);
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
    private StringTokenizer tokenizer;
    private BufferedReader reader;

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