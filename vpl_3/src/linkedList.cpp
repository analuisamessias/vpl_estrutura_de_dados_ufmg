#include "linkedList.hpp"
#include <cstddef>

LinkedList::LinkedList() : head(nullptr), listSize(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkedList::addNode(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    listSize++;
}

Node* LinkedList::begin() const {
    return head;
}

int LinkedList::size() const {
    return listSize;
}

void LinkedList::addNodeAtEnd(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    listSize++;  //aumenta tamanho da lista
}