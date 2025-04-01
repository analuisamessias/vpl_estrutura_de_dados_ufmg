#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

struct Node {
    int value;
    Node* next;
    
    Node(int val) : value(val), next(nullptr) {}  // Construtor adicionado
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void addNode(int value);
    Node* begin() const;
    int size() const;
    void addNodeAtEnd(int value);  // Método já declarado anteriormente

private:
    Node* head;
    int listSize;
};

#endif // LINKEDLIST_HPP