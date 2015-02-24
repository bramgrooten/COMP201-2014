#include <iostream>
#include <string>

// Singly-linked-list
// Parameterized type
template <typename T>
class Node {
public:
    Node (T d, Node * n, Node * p) { data = d; next = n; prev = p; }
    Node(T d, Node * n) { data = d; next = n; prev = NULL; }
    Node(T d)           { data = d; next = NULL; prev = NULL; }
    T data;
    Node * next;
    Node * prev;
};

template <typename T>
class List {
public:
    List() {
        head = NULL;
        tail = NULL;
    }
    void push_front(T element) {
        Node<T> * node = new Node<T>(element, head);
        Node<T> * otherNode;
        // if list is empty
        // also adjust tail..
        // else:
        otherNode = head;
        otherNode->prev = node;
        head = node;
    }
    T peek_front() {
        return head->data;
    }
    void pop_front() {
        Node<T> * node;
        node = head->next;
        delete head;
        head = node;
    }
    // make these 3 methods yourself:
    void push_back(T element) {
        Node<T> * node = new Node<T>(element,NULL, tail);
        Node<T> * otherNode;
        // if list is empty
        // also adjust head
        // else:
        otherNode = tail->prev;
        tail = node;
        otherNode->next = node;
    }
    T peek_back() {
        return tail->data;
    }
    void pop_back() {
        Node<T> * node;
        node = tail->prev;
        delete tail;
        tail = node;
    }
    
    bool empty() {
        return head == NULL && tail == NULL;
    }
private:
    Node<T> * head;
    Node<T> * tail;
};

int main() {
    List<int> numbers;
    numbers.push_back(42);
    numbers.push_front(10);
    numbers.push_front(3);
    numbers.push_back(87);
    // 3, 10, 42, 87
    std::cout << (3 == numbers.peek_front()) << std::endl;
    std::cout << (87 == numbers.peek_back()) << std::endl;
    numbers.pop_front();
    // 10, 42, 87
    std::cout << (10 == numbers.peek_front()) << std::endl;
    numbers.pop_back();
    // 10, 42
    std::cout << (42 == numbers.peek_back()) << std::endl;
    std::cout << !numbers.empty() << std::endl;
    numbers.pop_back();
    numbers.pop_back();
    std::cout << numbers.empty() << std::endl;
    
    return 0;
}