import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        ArrayList<ArrayList<Integer>> graphTr = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            graph.add(new ArrayList<>());
            graphTr.add(new ArrayList<>());
        }
        String previous = scanner.next();
        HashSet<Integer> ban = new HashSet<>();
        if (previous.length() > 1) {
            ban.add(Solver.charToNum(previous.charAt(0)));
        }
        for (int i = 1; i < n; i++) {
            String cur = scanner.next();
            if (cur.length() < previous.length()) {
                System.out.println("No");
                return;
            }
            if (cur.length() > 1) {
                ban.add(Solver.charToNum(cur.charAt(0)));
            }
            int pos = Solver.calcPos(previous, cur);
            if (pos == cur.length()) {
                System.out.println("No");
                return;
            }
            if (pos == -1) {
                previous = cur;
                continue;
            }
            int left = Solver.charToNum(previous.charAt(pos));
            int right = Solver.charToNum(cur.charAt(pos));
            graph.get(left).add(right);
            graphTr.get(right).add(left);
            previous = cur;
        }
        HashSet<Integer> sources = new HashSet<>();
        for (int i = 0; i < graphTr.size(); i++) {
            if (graphTr.get(i).size() == 0) {
                sources.add(i);
            }
        }
        Solver solver = new Solver(graph);
        if (solver.checkCycle()) {
            System.out.println("No");
            return;
        }
        ArrayList<Integer> topSort = solver.makeTopSort();
        int count = 1;
        boolean zeroAssigned = false;
        int[] ans = new int[26];
        for (int i : topSort) {
            if (!ban.contains(i) && sources.contains(i) && !zeroAssigned) {
                ans[i] = 0;
                zeroAssigned = true;
            } else {
                ans[i] = count++;
            }
        }
        if (!zeroAssigned) {
            System.out.println("No");
        } else {
            System.out.println("Yes");
            for (int i : ans) {
                System.out.print(i + " ");
            }
        }
    }
}

class Solver {
    private ArrayList<ArrayList<Integer>> graph;
    private ArrayList<Integer> colors, topSort;

    public Solver(ArrayList<ArrayList<Integer>> graph) {
        this.graph = graph;
        colors = new ArrayList<>();
        topSort = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            colors.add(0);
        }
    }

    private boolean checkCycle(int cur) {
        colors.set(cur, 1);
        for (int to : graph.get(cur)) {
            if (colors.get(to) == 1) {
                return true;
            } else if (colors.get(to) == 0) {
                if (checkCycle(to)) {
                    return true;
                }
            }
        }
        colors.set(cur, 2);
        return false;
    }

    public boolean checkCycle() {
        for (int i = 0; i < 26; i++) {
            if (colors.get(i) == 0) {
                if (checkCycle(i)) {
                    return true;
                }
            }
        }
        return false;
    }

    private void dfs(int cur) {
        colors.set(cur, 1);
        for (int to : graph.get(cur)) {
            if (colors.get(to) != 1) {
                dfs(to);
            }
        }
        topSort.add(cur);
    }

    public ArrayList<Integer> makeTopSort() {
        for (int i = 0; i < 26; i++) {
            colors.set(i, 0);
        }
        for (int i = 25; i >= 0; i--) {
            if (colors.get(i) == 0) {
                dfs(i);
            }
        }
        Collections.reverse(topSort);
        return topSort;
    }

    public static int calcPos(String first, String second) {
        if (first.length() != second.length()) {
            return -1;
        }
        for (int i = 0; i < first.length(); i++) {
            if (first.charAt(i) != second.charAt(i)) {
                return i;
            }
        }
        return first.length();
    }

    public static int charToNum(char ch) {
        return ch - 'a';
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
