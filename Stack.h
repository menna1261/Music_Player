#ifndef STACK_H
#define STACK_H
#include <iostream>

template <typename T, int MAX_SIZE = 10>
class Stack {
private:
    T arr[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    // Function to check if the stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Function to check if the stack is full
    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    // Function to push an element onto the stack
    void push(const T& element) {
        if (isFull()) {
            std::cout << "Stack is full. Cannot push more elements." << std::endl;
        } else {
            arr[++top] = element;
            //std::cout << "Pushed: " << element << std::endl;
        }
    }

    // Function to pop an element from the stack
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty. Cannot pop elements." << std::endl;
        } else {
            std::cout << "Popped: " << arr[top--] << std::endl;
        }
    }

    // Function to display the elements in the stack
    void display() const {
       cout<<endl;
            for (int i = 0; i <= top; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

};
#endif
