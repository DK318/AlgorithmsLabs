import javax.management.MBeanRegistration;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), l = scanner.nextInt();
        ArrayList<Integer> seq = new ArrayList<>();
        for (int i = 0; i < l; i++) {
            seq.add(scanner.nextInt() - 1);
        }
        Solver solver = new Solver(n, l, seq);
        ArrayList<Pair<Integer, Integer>> edges = solver.solve();
        System.out.println(edges.size());
        for (Pair<Integer, Integer> edge : edges) {
            System.out.printf("%d %d\n", edge.first + 1, edge.second + 1);
        }
    }
}

class Solver {
    private int n, m;
    private int pos = 0;
    private ArrayList<Integer> seq;
    private ArrayList<HashSet<Integer>> edgeSet;
    private ArrayList<Pair<Integer, Integer>> edges;

    public Solver(int n, int m, ArrayList<Integer> seq) {
        this.n = n;
        this.m = m;
        this.seq = seq;
        edges = new ArrayList<>();
        edgeSet = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            edgeSet.add(new HashSet<>());
        }
    }

    private void build(int cur, int parent) {
        while (pos < m) {
            if (seq.get(pos) != parent) {
                pos++;
                build(seq.get(pos - 1), cur);
            } else {
                edges.add(new Pair<>(parent, cur));
                edgeSet.get(parent).add(cur);
                for (int to : edgeSet.get(cur)) {
                    if (to > cur) {
                        edges.add(new Pair<>(parent, to));
                    }
                    edgeSet.get(parent).add(to);
                }
                pos++;
                break;
            }
        }
    }

    private void build() {
        build(seq.get(0), -1);
    }

    public ArrayList<Pair<Integer, Integer>> solve() {
        build();
        return edges;
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