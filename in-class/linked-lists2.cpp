#include <iostream>
#include <string>
// #define NULL ((void *)0)
template <typename T>
class Node {
public:
    Node(T d, Node<T> * n) { data = d; next = n; }
    Node(T d)              { data = d; next = NULL; }
    T data;
    Node<T> * next;
};
template <typename T>
class Stack {
public:
    Stack() {
        head = NULL;
    }
    void push (T data) {
        Node<T> * node = new Node<T>(data, head);
        head = node;
    }
    void pop() {
        Node<T> * node = head->next;
        delete head;
        head = node;
    }
    T top() {
        return head->data;
    }
    bool empty() {
        return head == NULL;
    }
private:
    Node<T> * head;
};

int main() {
    Stack<std::string> stack;
    stack.push("world");
    stack.push("cruel");
    stack.push("hello");
    std::cout << stack.top() << std::endl;
    
    Node<std::string> * first = new Node<std::string>("hi");
    Node<std::string> * second = new Node<std::string>("world");
    first->next = second;
    
    for (Node<std::string> * pointer = first;
        pointer != NULL;
        pointer = pointer->next) {
        std::cout << pointer->data << std::endl;
    }
//    for (/* init */; /* condition */; /* update */) {
//    }
    delete first;
    delete second;
    return 0;
}


