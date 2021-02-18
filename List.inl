
template<typename T>
List<T>::List() : _size(0), _head(nullptr), _tail(nullptr)
{}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
T &List<T>::operator[](const size_t &index) {
    if (index < 0 || index > _size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    Node *current;
    if (index < _size / 2 + 1) {
        current = _head;
        for (size_t i = 0; i < index; ++i) {
            current = current->__next;
        }
    } else {
        current = _tail;
        for (size_t i = _size - 1; i > index; --i) {
            current = current->__prev;
        }
    }
    return current->__data;
}

template<typename T>
void List<T>::push_back(T data) {
    if (_head == nullptr) {
        _head = new Node(data);
        _tail = _head;
    }
    else {
        _tail->__next = new Node(data, _tail);
        _tail = _tail->__next;
    }
    ++_size;
}

template<typename T>
void List<T>::push_front(T data) {
    if (_head == nullptr) {
        _head = new Node(data);
        _tail = _head;
    }
    else {
        _head->__prev = new Node(data, nullptr, _head);
        _head = _head->__prev;
    }
    ++_size;
}

template<typename T>
void List<T>::pop_front() {
    Node *temp = _head;
    _head = _head->__next;
    if (_head) {
        _head->__prev = nullptr;
    }

    delete temp;

    --_size;
}

template<typename T>
void List<T>::pop_back() {
    Node *temp = _tail;
    _tail = _tail->__prev;
    if (_tail) {
        _tail->__next = nullptr;
    }

    delete temp;

    --_size;
}

template<typename T>
void List<T>::clear() {
    while (_size) {
        pop_front();
    }
}

template<typename T>
void List<T>::insert(T data, size_t index) {
    if (index < 0 || index > _size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    if (index == 0) {
        push_front(data);
    } else if (index == _size - 1) {
        push_back(data);
    } else {
        if (index < _size / 2 + 1) {
            Node *previous = _head;

            for (size_t i = 0; i < index - 1; ++i) {
                previous = previous->__next;
            }

            Node *newNode = new Node(data, previous, previous->__next);
            previous->__next->__prev = newNode;
            previous->__next = newNode;
        }
        else {
            Node *next = _tail;

            for (size_t i = _size - 1; i > index + 1; --i) {
                next = next->__prev;
            }

            Node *newNode = new Node(data, next->__prev, next);
            next->__prev->__next = newNode;
            next->__prev = newNode;
        }
    }
    ++_size;
}

template<typename T>
void List<T>::remove(size_t index) {
    if (index < 0 || index > _size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    if (index == 0) {
        pop_front();
    } else if (index == _size - 1) {
        pop_back();
    } else {
        if (index < _size / 2 + 1) {
            Node *previous = _head;

            for (size_t i = 0; i < index - 1; ++i) {
                previous = previous->__next;
            }

            Node *toDelete = previous->__next;
            previous->__next = toDelete->__next;
            toDelete->__next->__prev = previous;

            delete toDelete;
        } else {
            Node *next = _tail;

            for (size_t i = _size - 1; i > index + 1; --i) {
                next = next->__prev;
            }

            Node *toDelete = next->__prev;
            next->__prev = toDelete->__prev;
            toDelete->__prev->__next = next;

            delete toDelete;
        }
    }
    --_size;
}

template<typename T>
bool List<T>::is_empty() const {
    return !_size;
}

template<typename T>
size_t List<T>::size() const {
    return _size;
}

template<typename T>
void List<T>::show() const {
    Node *current = _head;
    while (current) {
        std::cout << current->__data << std::endl;
        current = current->__next;
    }
}

template<typename T>
size_t List<T>::find(const T &rhs) const {
    size_t counter = 0;
    Node *current = _head;
    while (current) {
        if (current->__data == rhs) {
            return counter;
        }
        current = current->__next;
        ++counter;
    }
    return -1;
}
