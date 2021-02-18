#ifndef PROTOTYPE_OF_HOMEWORK3_LIST_HPP
#define PROTOTYPE_OF_HOMEWORK3_LIST_HPP
#include <iostream>

template<typename T>
class List {
public:
    class Iterator;

    List();

    ~List();

    T& operator[](const size_t& index);

    void push_back(T data);
    void push_front(T data);
    void pop_front();
    void pop_back();
    void clear();
    void insert(T data, size_t index);
    void remove(size_t index);
    bool isEmpty() const;
    size_t getSize() const;
    void show() const;
    size_t find(const T& rhs) const;

    Iterator begin() {return Iterator(head);}
    Iterator end() {return Iterator(nullptr);}

private:
    struct Node;

    size_t Size;
    Node *head;
    Node *tail;

    struct Node {
        T data;
        Node *next;
        Node *prev;

        explicit Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
            this->data = data;
            this->next = pNext;
            this->prev = pPrev;
        }
    };

public:
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* first) : current(first) { }

        Iterator operator+(int n) {
            for (int i = 0; i < n && current != nullptr; ++i) {
                current = current->next;
            }
            return current;
        }

        Iterator operator-(int n) {
            for (int i = 0; i < n && current != nullptr; ++i) {
                current = current->prev;
            }
            return current;
        }

        Iterator operator++() {
            current = current->next;
            return current;
        }

        Iterator operator--() {
            current = current->prev;
            return current;
        }

        T& operator*() const { return current->data; }

        bool operator==(const Iterator &rhs) const { return current == rhs.current; }

        bool operator!=(const Iterator &rhs) const { return current != rhs.current; }
    };
};


#include "List.inl"

#endif //PROTOTYPE_OF_HOMEWORK3_LIST_HPP
