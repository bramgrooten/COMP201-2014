#include <iostream>
#include <string>

// Singly-linked-list
// Parameterized type
template <typename T>
class Node {
public:
    Node(T d, Node * n) { data = d; next = n; }
    Node(T d)           { data = d; next = NULL; }
    T data;
    Node * next;
};

template <typename T>
class Stack {
    Stack() {
        head = NULL;
    }
    void push(T element) {
        Node<T> * node = new Node<T>(element, head);
        head = node;
    }
    T peek() {
        return head->data;
    }
    void pop() {
        Node<T> * node;
        node = head->next;
        delete head;
        head = node;
    }
    bool empty() {
        return head == NULL;
    }
private:
    Node<T> * head;
};

int main() {
    Node<std::string> * node2 = new Node<std::string>("world");
    Node<std::string> * node1 = new Node<std::string>("hello", node2);
    Node<float> number2(2.0);
    Node<float> number1(1.0, &number2);
    
    for (Node<std::string> * pointer = node1;
        pointer != NULL;
        pointer = pointer->next) {
        std::cout << pointer->data << " ";
    }
    
    return 0;
}