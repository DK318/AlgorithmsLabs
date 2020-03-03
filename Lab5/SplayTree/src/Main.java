import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        SplayTree tree = new SplayTree();
        while (in.hasNext()) {
            String type = in.next();
            int val = in.nextInt();
            switch (type) {
                case "insert":
                    tree.insert(val);
                    break;
                case "delete":
                    tree.delete(val);
                    break;
                case "exists":
                    System.out.println(tree.exists(val) ? "true" : "false");
                    break;
                case "next":
                    Node next = tree.next(val);
                    System.out.println(next == null ? "none" : next.value);
                    break;
                case "prev":
                    Node prev = tree.prev(val);
                    System.out.println(prev == null ? "none" : prev.value);
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
    int value;
    Node left;
    Node right;

    public Node(int value) {
        this.value = value;
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

class SplayTree {
    private Node root;

    private Node rightRotate(Node x) {
        Node temp = x.left;
        x.left = temp.right;
        temp.right = x;
        return temp;
    }

    private Node leftRotate(Node x) {
        Node temp = x.right;
        x.right = temp.left;
        temp.left = x;
        return temp;
    }

    private Node splay(Node current, int value) {
        if (current == null || current.value == value) {
            return current;
        }
        if (value < current.value) {
            if (current.left == null) {
                return current;
            }
            if (value < current.left.value) {
                current.left.left = splay(current.left.left, value);
                current = rightRotate(current);
            } else if (value > current.left.value) {
                current.left.right = splay(current.left.right, value);
                if (current.left.right != null) {
                    current.left = leftRotate(current.left);
                }
            }
            return current.left == null ? current : rightRotate(current);
        } else {
            if (current.right == null) {
                return current;
            }
            if (value < current.right.value) {
                current.right.left = splay(current.right.left, value);
                if (current.right.left != null) {
                    current.right = rightRotate(current.right);
                }
            } else if (value > current.right.value) {
                current.right.right = splay(current.right.right, value);
                current = leftRotate(current);
            }
            return current.right == null ? current : leftRotate(current);
        }
    }

    private int maximum(Node v) {
        return v.right == null ? v.value : maximum(v.right);
    }

    private Node merge(Node tree1, Node tree2) {
        if (tree1 == null) {
            return tree2;
        }
        if (tree2 == null) {
            return tree1;
        }
        int max = maximum(tree1);
        tree1 = splay(tree1, max);
        tree1.right = tree2;
        return tree1;
    }

    private Pair split(Node v, int x) {
        v = splay(v, x);
        if (v.value < x) {
            Node temp = v.right;
            v.right = null;
            return new Pair(v, temp);
        } else {
            Node temp = v.left;
            v.left = null;
            return new Pair(temp, v);
        }
    }

    public void insert(int x) {
        if (exists(x)) {
            return;
        }
        if (root == null) {
            root = new Node(x);
            return;
        }
        Pair pair = split(root, x);
        root = new Node(x);
        root.left = pair.first;
        root.right = pair.second;
    }

    public void delete(int x) {
        if (root == null) {
            return;
        }
        root = splay(root, x);
        if (root.value == x) {
            root = merge(root.left, root.right);
        }
    }

    public boolean exists(int x) {
        if (root == null) {
            return false;
        }
        root = splay(root, x);
        return root.value == x;
    }

    public Node next(int x) {
        Node current = root, successor = null;
        while (current != null) {
            if (x < current.value) {
                successor = current;
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return successor;
    }

    public Node prev(int x) {
        Node current = root, successor = null;
        while (current != null) {
            if (x > current.value) {
                successor = current;
                current = current.right;
            } else {
                current = current.left;
            }
        }
        return successor;
    }
}