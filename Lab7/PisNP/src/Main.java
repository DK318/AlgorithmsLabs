import javax.sound.midi.Soundbank;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), m = scanner.nextInt();
        Solver solver = new Solver(n);
        for (int i = 0; i < m; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            int c = scanner.nextInt();
            solver.add(a, b, c);
        }
        if (!solver.exists()) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
            ArrayList<Integer> ans = solver.getAns();
            for (int cur : ans) {
                System.out.print(cur + " ");
            }
        }
    }
}

class Solver {
    private int n;
    private ArrayList<ArrayList<Integer>> graph, graphTr;
    private ArrayList<Boolean> used;
    private ArrayList<Integer> order, comps;

    public Solver(int n) {
        this.n = n;
        graph = new ArrayList<>();
        graphTr = new ArrayList<>();
        comps = new ArrayList<>();
        order = new ArrayList<>();
        for (int i = 0; i < 2 * n; i++) {
            graph.add(new ArrayList<>());
            graphTr.add(new ArrayList<>());
            comps.add(0);
        }
    }

    private int notVar(int x) {
        return (x >= n ? x - n : x + n);
    }

    public void add(int a, int b, int c) {
        if (a < 0) {
            a = notVar(Math.abs(a) - 1);
        } else {
            a--;
        }
        if (b < 0) {
            b = notVar(Math.abs(b) - 1);
        } else {
            b--;
        }
        if (c < 0) {
            c = notVar(Math.abs(c) - 1);
        } else {
            c--;
        }
        int notA = notVar(a), notB = notVar(b), notC = notVar(c);
        addEdges(a, b, c, notA, notB, notC, graph);
        addEdges(notA, notB, notC, a, b, c, graphTr);
    }

    private void addEdges(int a, int b, int c, int notA, int notB, int notC, ArrayList<ArrayList<Integer>> graph) {
        graph.get(notA).add(b);
        graph.get(notA).add(c);
        graph.get(notB).add(a);
        graph.get(notB).add(c);
        graph.get(notC).add(a);
        graph.get(notC).add(b);
    }

    private void assignUsed() {
        used = new ArrayList<>();
        for (int i = 0; i < 2 * n; i++) {
            used.add(false);
        }
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

    private void dfs2(int cur, int color) {
        used.set(cur, true);
        comps.set(cur, color);
        for (int to : graphTr.get(cur)) {
            if (!used.get(to)) {
                dfs2(to, color);
            }
        }
    }

    public boolean exists() {
        assignUsed();
        for (int i = 0; i < 2 * n; i++) {
            if (!used.get(i)) {
                dfs1(i);
            }
        }
        Collections.reverse(order);
        int curColor = 0;
        assignUsed();
        for (int cur : order) {
            if (!used.get(cur)) {
                dfs2(cur, curColor);
                curColor++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (comps.get(i).equals(comps.get(notVar(i)))) {
                return false;
            }
        }
        return true;
    }

    public ArrayList<Integer> getAns() {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (comps.get(i) > comps.get(notVar(i))) {
                ans.add(i + 1);
            } else {
                ans.add(-i - 1);
            }
        }
        return ans;
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