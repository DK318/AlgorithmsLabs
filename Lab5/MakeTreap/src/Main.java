import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        Treap treap = new Treap();
        int n = in.nextInt();
        Pair[] keysAndPriorities = new Pair[n];
        for (int i = 0; i < n; i++) {
            int key = in.nextInt();
            int priority = in.nextInt();
            keysAndPriorities[i] = new Pair(key, priority, i + 1);
        }
        Arrays.sort(keysAndPriorities);
        for (int i = 0; i < n; i++) {
            treap.insert(keysAndPriorities[i]);
        }
        AnswerNode[] ans = treap.getAnswer(n);
        PrintWriter writer = new PrintWriter(System.out);
        writer.println("YES");
        for (int i = 1; i <= n; i++) {
            AnswerNode cur = ans[i];
            writer.print(cur.parent);
            writer.print(" ");
            writer.print(cur.left);
            writer.print(" ");
            writer.println(cur.right);
        }
        writer.flush();
        writer.close();
    }
}

class Scanner {
    BufferedInputStream in;

    final int bufSize = 1 << 16;
    final byte b[] = new byte[bufSize];

    Scanner(InputStream in ) {
        this.in = new BufferedInputStream(in, bufSize);
    }

    int nextInt() throws IOException {
        int c;
        while ((c = nextChar()) <= 32)
            ;
        int x = 0, sign = 1;
        if (c == '-') {
            sign = -1;
            c = nextChar();
        }
        while (c >= '0') {
            x = x * 10 + (c - '0');
            c = nextChar();
        }
        return x * sign;
    }

    StringBuilder _buf = new StringBuilder();
    String nextWord() throws IOException {
        int c;
        _buf.setLength(0);
        while ((c = nextChar()) <= 32 && c != -1)
            ;
        if (c == -1)
            return null;
        while (c > 32) {
            _buf.append((char)c);
            c = nextChar();
        }
        return _buf.toString();
    }

    int bn = bufSize, k = bufSize;

    int nextChar() throws IOException {
        if (bn == k) {
            k = in.read(b, 0, bufSize);
            bn = 0;
        }
        return bn >= k ? -1 : b[bn++];
    }

    int nextNotSpace() throws IOException {
        int ch;
        while ((ch = nextChar()) <= 32 && ch != -1)
            ;
        return ch;
    }
}

class Node {
    int key;
    int position;
    int priority;
    int size;
    Node left;
    Node right;
    Node parent;

    public Node(int key, int priority, int position) {
        this.key = key;
        this.priority = priority;
        this.position = position;
        size = 1;
        left = null;
        right = null;
        parent = null;
    }
}

class AnswerNode {
    int parent;
    int left;
    int right;

    public AnswerNode(int parent, int left, int right) {
        this.parent = parent;
        this.left = left;
        this.right = right;
    }
}

class Pair implements Comparable<Pair> {
    int first;
    int second;
    int position;

    public Pair(int first, int second, int position) {
        this.first = first;
        this.second = second;
        this.position = position;
    }

    @Override
    public int compareTo(Pair pair) {
        int res = first - pair.first;
        if (res == 0) {
            return second - pair.second;
        } else {
            return res;
        }
    }
}

class Treap {
    private Node root = null;
    private Node lastNode = null;

    public void insert(Pair nodeAndPosition) {
        Node node = new Node(nodeAndPosition.first, nodeAndPosition.second, nodeAndPosition.position);
        if (root == null) {
            root = node;
            lastNode = root;
            return;
        }
        while (lastNode != root && lastNode.priority > node.priority) {
            lastNode = lastNode.parent;
        }
        if (lastNode == root) {
            if (root.priority > node.priority) {
                root.parent = node;
                node.left = root;
                root = node;
                lastNode = root;
                return;
            }
        }
        node.left = lastNode.right;
        node.parent = lastNode;
        lastNode.right = node;
        if (node.left != null) {
            node.left.parent = node;
        }
        lastNode = node;
    }

    public AnswerNode[] getAnswer(int n) {
        AnswerNode[] res = new AnswerNode[n + 1];
        getAnswer(root, res);
        return res;
    }

    private void getAnswer(Node current, AnswerNode[] ans) {
        if (current != null) {
            getAnswer(current.left, ans);
            ans[current.position] = new AnswerNode(getPosition(current.parent), getPosition(current.left), getPosition(current.right));
            getAnswer(current.right, ans);
        }
    }

    private int getPosition(Node x) {
        return x == null ? 0 : x.position;
    }
}