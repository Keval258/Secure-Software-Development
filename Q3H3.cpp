#include <memory>
#include <stdexcept>

const int INITIAL_CAPACITY = 10;
const int EXPANSION_FACTOR = 2;

class Stack {
public:
    Stack() : data(new std::unique_ptr<std::string>[INITIAL_CAPACITY]), size(0), capacity(INITIAL_CAPACITY) {}

    void push(const std::string& item) {
        if (size == capacity) {
            expandCapacity();
        }

        data[size] = std::make_unique<std::string>(item);
        size++;
    }

    std::string pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }

        size--;
        std::string item = *data[size];
        data[size].reset();

        return item;
    }

private:
    std::unique_ptr<std::string>* data;
    int size;
    int capacity;

    void expandCapacity() {
        int newCapacity = capacity * EXPANSION_FACTOR;
        std::unique_ptr<std::string>* newData = new std::unique_ptr<std::string>[newCapacity];

        for (int i = 0; i < size; i++) {
            newData[i] = std::move(data[i]);
        }

        data = newData;
        capacity = newCapacity;
    }
};

int main() {
    Stack stack;

    try {
        stack.push("Hello");
        stack.push("World");

        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl; // Throws exception since the stack is empty
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
