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
        for (int i = 0; i < n; i++) {
            int type = in.nextInt();
            int key = in.nextInt();
            switch (type) {
                case 0:
                    System.out.println(treap.kthMaximum(key));
                    break;
                case 1:
                    treap.insert(key);
                    break;
                case -1:
                    treap.delete(key);
                    break;
            }
        }
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
    int key;
    int priority;
    int size;
    Node left;
    Node right;

    public Node(int key) {
        this.key = key;
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
    private Node root = null;

    private int getSize(Node x) {
        return x == null ? 0 : x.size;
    }

    private void updateSize(Node x) {
        if (x != null) {
            x.size = getSize(x.left) + getSize(x.right) + 1;
        }
    }

    private Pair split(Node current, int key) {
        if (current == null) {
            return new Pair(null, null);
        }
        if (key > current.key) {
            Pair pair = split(current.right, key);
            current.right = pair.first;
            updateSize(current);
            return new Pair(current, pair.second);
        } else {
            Pair pair = split(current.left, key);
            current.left = pair.second;
            updateSize(current);
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
            updateSize(t1);
            return t1;
        } else {
            t2.left = merge(t1, t2.left);
            updateSize(t2);
            return t2;
        }
    }

    public void insert(int key) {
        Pair pair = split(root, key);
        root = merge(merge(pair.first, new Node(key)), pair.second);
    }

    public void delete(int key) {
        Pair pair1 = split(root, key);
        Pair pair2 = split(pair1.second, key + 1);
        root = merge(pair1.first, pair2.second);
    }

    private int kthMaximum(Node current, int k) {
        if (getSize(current.right) + 1 == k) {
            return current.key;
        }
        if (getSize(current.right) >= k) {
            return kthMaximum(current.right, k);
        } else {
            return kthMaximum(current.left, k - getSize(current.right) - 1);
        }
    }

    public int kthMaximum(int k) {
        return kthMaximum(root, k);
    }
}