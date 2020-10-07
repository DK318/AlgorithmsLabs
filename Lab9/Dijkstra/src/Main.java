import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int s = scanner.nextInt() - 1;
        int f = scanner.nextInt() - 1;
        ArrayList<ArrayList<Pair>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long w = scanner.nextInt();
                if (w > 0) {
                    graph.get(i).add(new Pair(w, j));
                }
            }
        }
        Solver solver = new Solver(n, s, f, graph);
        System.out.println(solver.dijkstra());
    }
}

class Solver {
    private int n, start, finish;
    private ArrayList<ArrayList<Pair>> graph;
    private ArrayList<Long> dist;

    public Solver(int n, int start, int finish, ArrayList<ArrayList<Pair>> graph) {
        this.n = n;
        this.start = start;
        this.finish = finish;
        this.graph = graph;
    }

    public long dijkstra() {
        dist = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            dist.add(Long.MAX_VALUE - (long) 1e9 - 100);
        }
        dist.set(start, 0L);
        TreeSet<Pair> set = new TreeSet<>();
        set.add(new Pair(0, start));
        while (!set.isEmpty()) {
            int cur = set.iterator().next().second;
            set.remove(set.iterator().next());
            for (Pair vertex : graph.get(cur)) {
                if (dist.get(cur) + vertex.first < dist.get(vertex.second)) {
                    set.remove(new Pair(dist.get(vertex.second), vertex.second));
                    dist.set(vertex.second, dist.get(cur) + vertex.first);
                    set.add(new Pair(dist.get(vertex.second), vertex.second));
                }
            }
        }
        long res = dist.get(finish);
        if (res == Long.MAX_VALUE - (long) 1e9 - 100) {
            return -1;
        } else {
            return res;
        }
    }
}

class Pair implements Comparable<Pair> {
    public long first;
    public int second;

    public Pair(long first, int second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public int compareTo(Pair pair) {
        if (first < pair.first) {
            return -1;
        } else if (first == pair.first) {
            return second - pair.second;
        } else {
            return 1;
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