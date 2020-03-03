import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BinaryTree tree = new BinaryTree();
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

class BinaryTree {
    private Node root = null;

    private Node insertRec(Node current, int value) {
        if (current == null) {
            return new Node(value);
        }
        if (value < current.value) {
            current.left = insertRec(current.left, value);
        } else if (value > current.value) {
            current.right = insertRec(current.right, value);
        }
        return current;
    }

    public void insert(int x) {
        root = insertRec(root, x);
    }

    private int minimum(Node x) {
        return x.left == null ? x.value : minimum(x.left);
    }

    private Node deleteRec(Node current, int value) {
        if (current == null) {
            return null;
        }
        if (value == current.value) {
            if (current.left == null && current.right == null) {
                return null;
            }
            if (current.right == null) {
                return current.left;
            }
            if (current.left == null) {
                return current.right;
            }
            int min = minimum(current.right);
            current.value = min;
            current.right = deleteRec(current.right, min);
            return current;
        }
        if (value < current.value) {
            current.left = deleteRec(current.left, value);
            return current;
        }
        current.right = deleteRec(current.right, value);
        return current;
    }

    public void delete(int x) {
        root = deleteRec(root, x);
    }

    private boolean existsRec(Node current, int value) {
        if (current == null) {
            return false;
        }
        if (value == current.value) {
            return true;
        }
        return value < current.value
                ? existsRec(current.left, value)
                : existsRec(current.right, value);
    }

    public boolean exists(int x) {
        return existsRec(root, x);
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