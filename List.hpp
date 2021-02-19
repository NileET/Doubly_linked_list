#ifndef LIST_HPP
#define LIST_HPP
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
    bool is_empty() const;
    size_t size() const;
    void show() const;
    size_t find(const T& rhs) const;

    Iterator begin() {return Iterator(_head);}
    Iterator end() {return Iterator(nullptr);}

private:
    struct Node;

    size_t _size;
    Node *_head;
    Node *_tail;

    struct Node {
        T __data;
        Node *__next;
        Node *__prev;

        explicit Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
            __data = data;
            __next = pNext;
            __prev = pPrev;
        }
    };

public:
    class Iterator {
    private:
        Node* __current;
    public:
        Iterator(Node* first) : __current(first) { }

        Iterator operator+(int n) {
            for (int i = 0; i < n && __current != nullptr; ++i) {
                __current = __current->__next;
            }
            return __current;
        }

        Iterator operator-(int n) {
            for (int i = 0; i < n && __current != nullptr; ++i) {
                __current = __current->__prev;
            }
            return __current;
        }

        Iterator operator++() {
            __current = __current->__next;
            return __current;
        }

        Iterator operator--() {
            __current = __current->__prev;
            return __current;
        }

        T& operator*() const { return __current->__data; }

        bool operator==(const Iterator &rhs) const { return __current == rhs.__current; }

        bool operator!=(const Iterator &rhs) const { return __current != rhs.__current; }
    };
};


#include "List.inl"

#endif //LIST_HPP
