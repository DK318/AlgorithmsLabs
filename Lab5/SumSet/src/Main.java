import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Treap treap = new Treap();
        int n = in.nextInt();
        boolean wasLastSum = false;
        long lastSum = 0;
        for (int i = 0; i < n; i++) {
            String query = in.next();
            if (query.equals("+")) {
                int x = in.nextInt();
                if (wasLastSum) {
                    x += lastSum;
                    x %= 1000000000;
                }
                wasLastSum = false;
                treap.insert(x);
            } else {
                int left = in.nextInt();
                int right = in.nextInt();
                wasLastSum = true;
                lastSum = treap.rangeSum(left, right);
                System.out.println(lastSum);
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

class Node {
    long key;
    int priority;
    long sum;
    Node left = null;
    Node right = null;

    public Node(long key) {
        this.key = key;
        priority = (int) (Math.random() * 1000000000);
        sum = key;
    }
}

class Pair {
    Node first;
    Node second;

    public Pair(Node first, Node second) {
        this.first = first;
        this.second = second;
    }
}

class Treap {
    private Node root = null;

    private long getSum(Node x) {
        return x == null ? 0 : x.sum;
    }

    private void updateSum(Node x) {
        if (x != null) {
            x.sum = getSum(x.left) + getSum(x.right) + x.key;
        }
    }

    private Pair split(Node current, long key) {
        if (current == null) {
            return new Pair(null, null);
        }
        if (key > current.key) {
            Pair pair = split(current.right, key);
            current.right = pair.first;
            updateSum(current);
            updateSum(pair.second);
            return new Pair(current, pair.second);
        } else {
            Pair pair = split(current.left, key);
            current.left = pair.second;
            updateSum(current);
            updateSum(pair.first);
            return new Pair(pair.first, current);
        }
    }

    private Node merge(Node t1, Node t2) {
        if (t2 == null) {
            return t1;
        }
        if (t1 == null) {
            return t2;
        }
        if (t1.priority > t2.priority) {
            t1.right = merge(t1.right, t2);
            updateSum(t1);
            return t1;
        } else {
            t2.left = merge(t1, t2.left);
            updateSum(t2);
            return t2;
        }
    }

    private boolean contains(long key) {
        Pair pair1 = split(root, key);
        Pair pair2 = split(pair1.second, key + 1);
        boolean res = (pair2.first != null);
        root = merge(merge(pair1.first, pair2.first), pair2.second);
        return res;
    }

    public void insert(long key) {
        if (contains(key)) {
            return;
        }
        Pair pair = split(root, key);
        root = merge(merge(pair.first, new Node(key)), pair.second);
    }

    public long rangeSum(int left, int right) {
        Pair pair1 = split(root, left);
        Pair pair2 = split(pair1.second, right + 1);
        long answer = getSum(pair2.first);
        root = merge(merge(pair1.first, pair2.first), pair2.second);
        return answer;
    }
}