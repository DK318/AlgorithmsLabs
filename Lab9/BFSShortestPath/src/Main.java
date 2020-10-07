import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), m = scanner.nextInt();
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt() - 1;
            int v = scanner.nextInt() - 1;
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        Solver solver = new Solver(n, graph);
        ArrayList<Integer> ans = solver.bfs();
        for (int cur : ans) {
            System.out.print(cur + " ");
        }
    }
}

class Solver {
    private int n;
    private ArrayList<ArrayList<Integer>> graph;
    private ArrayList<Integer> dist;

    public Solver(int n, ArrayList<ArrayList<Integer>> graph) {
        this.n = n;
        this.graph = graph;
        dist = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            dist.add((int) 1e9);
        }
    }

    public ArrayList<Integer> bfs() {
        Queue<Integer> queue = new ArrayDeque<>();
        queue.add(0);
        dist.set(0, 0);
        while (!queue.isEmpty()) {
            int cur = queue.remove();
            for (int to : graph.get(cur)) {
                if (dist.get(to) == (int) 1e9) {
                    dist.set(to, dist.get(cur) + 1);
                    queue.add(to);
                }
            }
        }
        return dist;
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