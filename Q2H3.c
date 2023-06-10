#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define EXPANSION_FACTOR 2

// Response object structure
typedef struct {
    bool success;
    int error_code;
} Response;

// Stack structure
typedef struct {
    char** data;
    int size;
    int capacity;
} Stack;

// Function prototypes
Stack* create_stack();
Response push(Stack* stack, const char* item);
Response pop(Stack* stack, char** item);
void free_stack(Stack* stack);

// Create an empty stack
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

// Push an item onto the stack
Response push(Stack* stack, const char* item) {
    if (stack->size == stack->capacity) {
        // Stack is full, expand the capacity
        int new_capacity = stack->capacity * EXPANSION_FACTOR;
        char** new_data = (char**)realloc(stack->data, new_capacity * sizeof(char*));
        if (new_data == NULL) {
            Response response = { false, 1 };
            return response; // Error: Memory allocation failed
        }
        stack->data = new_data;
        stack->capacity = new_capacity;
    }

    // Copy the item into the stack
    char* new_item = strdup(item);
    if (new_item == NULL) {
        Response response = { false, 2 };
        return response; // Error: Memory allocation failed
    }
    stack->data[stack->size++] = new_item;

    Response response = { true, 0 };
    return response; // Success
}

// Pop an item from the stack
Response pop(Stack* stack, char** item) {
    if (stack->size == 0) {
        Response response = { false, 3 };
        return response; // Error: Stack is empty
    }

    *item = stack->data[--stack->size];
    stack->data[stack->size] = NULL;

    Response response = { true, 0 };
    return response; // Success
}

// Free the stack and its data
void free_stack(Stack* stack) {
    for (int i = 0; i < stack->size; i++) {
        free(stack->data[i]);
    }
    free(stack->data);
    free(stack);
}

// Example usage
int main() {
    Stack* stack = create_stack();

    // Push items onto the stack
    Response response = push(stack, "Hello");
    if (!response.success) {
        fprintf(stderr, "Error pushing item onto stack. Error code: %d\n", response.error_code);
        free_stack(stack);
        return 1;
    }

    response = push(stack, "World");
    if (!response.success) {
        fprintf(stderr, "Error pushing item onto stack. Error code: %d\n", response.error_code);
        free_stack(stack);
        return 1;
    }

    // Pop items from the stack
    char* item;
    response = pop(stack, &item);
    if (!response.success) {
        fprintf(stderr, "Error popping item from stack. Error code: %d\n", response.error_code);
        free_stack(stack);
        return 1;
    }
    printf("Popped item: %s\n", item);
    free(item);

    response = pop(stack, &item);
    if (!response.success) {
        fprintf(stderr, "Error popping item from stack. Error code: %d\n", response.error_code);
        free_stack(stack);
        return 1;
    }
    printf("Popped item: %s\n", item);
    free(item);

    free_stack(stack);
    return 0;
}
