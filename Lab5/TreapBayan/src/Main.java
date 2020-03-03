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
        Treap treap = new Treap(n);
        for (int i = 0; i < m; i++) {
            int left, right;
            left = in.nextInt();
            right = in.nextInt();
            treap.query(left, right);
        }
        treap.show();
    }
}

class Scanner {
    private BufferedReader reader;
    private StringTokenizer tokenizer;
    private String buffer;

    public Scanner(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
        buffer = "";
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            if (!buffer.equals("")) {
                tokenizer = new StringTokenizer(buffer);
                buffer = "";
                break;
            }
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

    public boolean hasNext() {
        if (!buffer.equals("")) {
            return true;
        }
        try {
            buffer = reader.readLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return buffer != null;
    }
}

class Node {
    int value;
    int priority;
    int size;
    Node left;
    Node right;

    public Node(int value) {
        this.value = value;
        priority = (int) (Math.random() * 1000000000);
        size = 1;
        left = null;
        right = null;
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
    private Node root;

    public Treap(int size) {
        root = null;
        for (int i = 0; i < size; i++) {
            root = merge(root, new Node(i + 1));
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
        int leftSize = getSize(current.left);
        if (leftSize >= k) {
            Pair pair = split(current.left, k);
            current.left = pair.second;
            updateSize(current);
            return new Pair(pair.first, current);
        } else {
            Pair pair = split(current.right, k - leftSize - 1);
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

    public void query(int left, int right) {
        Pair pair1 = split(root, right);
        Pair pair2 = split(pair1.first, left - 1);
        root = merge(merge(pair2.second, pair2.first), pair1.second);
    }

    public void show() {
        show(root);
    }

    private void show(Node current) {
        if (current == null) {
            return;
        }
        show(current.left);
        System.out.print(current.value + " ");
        show(current.right);
    }
}