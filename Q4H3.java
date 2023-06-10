import java.util.Arrays;
import java.util.EmptyStackException;

public class Stack {
    private String[] data;
    private int size;
    private int capacity;

    private static final int INITIAL_CAPACITY = 10;
    private static final int EXPANSION_FACTOR = 2;

    public Stack() {
        data = new String[INITIAL_CAPACITY];
        size = 0;
        capacity = INITIAL_CAPACITY;
    }

    public void push(String item) {
        if (size == capacity) {
            expandCapacity();
        }

        data[size] = item;
        size++;
    }

    public String pop() {
        if (size == 0) {
            throw new EmptyStackException();
        }

        size--;
        String item = data[size];
        data[size] = null;

        return item;
    }

    private void expandCapacity() {
        int newCapacity = capacity * EXPANSION_FACTOR;
        data = Arrays.copyOf(data, newCapacity);
        capacity = newCapacity;
    }

    public static void main(String[] args) {
        Stack stack = new Stack();

        try {
            stack.push("Hello");
            stack.push("World");

            System.out.println(stack.pop());
            System.out.println(stack.pop());
            System.out.println(stack.pop()); // Throws exception since the stack is empty
        } catch (EmptyStackException e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
    }
}
