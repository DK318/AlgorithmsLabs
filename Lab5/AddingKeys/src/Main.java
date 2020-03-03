import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        Treap treap = new Treap(n, m);
        for (int i = 0; i < n; i++) {
            int pos = in.nextInt();
            treap.insert(i + 1, pos - 1);
        }
        treap.show();
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
    int value;
    int priority;
    int size = 1;
    Node left = null;
    Node right = null;

    public Node(int value) {
        this.value = value;
        priority = (int) (Math.random() * 1000000000);
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
    private int[] nearestZero;
    private int rightistNonZeroPos;

    public Treap(int n, int m) {
        rightistNonZeroPos = 0;
        nearestZero = new int[n + m];
        for (int i = 0; i < n + m; i++) {
            root = merge(root, new Node(0));
            nearestZero[i] = i;
        }
    }

    private int getSize(Node x) {
        return x == null ? 0 : x.size;
    }

    private void updateSize(Node x) {
        if (x != null) {
            x.size = getSize(x.left) + getSize(x.right) + 1;
        }
    }

    private Pair split(Node current, int k) {
        if (current == null) {
            return new Pair(null, null);
        }
        int l = getSize(current.left);
        if (l >= k) {
            Pair pair = split(current.left, k);
            current.left = pair.second;
            updateSize(current);
            return new Pair(pair.first, current);
        } else {
            Pair pair = split(current.right, k - l - 1);
            current.right = pair.first;
            updateSize(current);
            return new Pair(current, pair.second);
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
            updateSize(t1);
            return t1;
        } else {
            t2.left = merge(t1, t2.left);
            updateSize(t2);
            return t2;
        }
    }

    private int findNearestZero(int pos) {
        if (nearestZero[pos] != pos) {
            nearestZero[pos] = findNearestZero(nearestZero[pos]);
        }
        return nearestZero[pos];
    }

    public void insert(int x, int pos) {
        int zeroPos = findNearestZero(pos);
        if (zeroPos > rightistNonZeroPos) {
            rightistNonZeroPos = zeroPos;
        }
        nearestZero[zeroPos] = findNearestZero(zeroPos + 1);
        delete(zeroPos);
        Pair pair = split(root, pos);
        root = merge(merge(pair.first, new Node(x)), pair.second);
    }

    private void delete(int pos) {
        Pair pair1 = split(root, pos);
        Pair pair2 = split(pair1.second, 1);
        root = merge(pair1.first, pair2.second);
    }

    public void show() {
        root = split(root, rightistNonZeroPos + 1).first;
        System.out.println(rightistNonZeroPos + 1);
        show(root);
    }

    private void show(Node current) {
        if (current != null) {
            show(current.left);
            System.out.print(current.value + " ");
            show(current.right);
        }
    }
}