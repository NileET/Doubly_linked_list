
template<typename T>
List<T>::List() : Size(0), head(nullptr), tail(nullptr)
{}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node(data);
        tail = head;
    }
    else {
        tail->next = new Node(data, tail);
        tail = tail->next;
    }
    ++Size;
}

template<typename T>
void List<T>::push_front(T data) {
    if (head == nullptr) {
        head = new Node(data);
        tail = head;
    }
    else {
        head->prev = new Node(data, nullptr, head);
        head = head->prev;
    }
    ++Size;
}

template<typename T>
void List<T>::pop_front() {
    Node *temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }

    delete temp;

    --Size;
}

template<typename T>
void List<T>::pop_back() {
    Node *temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    }

    delete temp;

    --Size;
}

template<typename T>
void List<T>::clear() {
    while (Size) {
        pop_front();
    }
}

template<typename T>
void List<T>::insert(T data, size_t index) {
    if (index < 0 || index > Size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    if (index == 0) {
        push_front(data);
    } else if (index == Size - 1) {
        push_back(data);
    } else {
        if (index < Size / 2 + 1) {
            Node *previous = this->head;

            for (size_t i = 0; i < index - 1; ++i) {
                previous = previous->next;
            }

            Node *newNode = new Node(data, previous, previous->next);
            previous->next->prev = newNode;
            previous->next = newNode;
        }
        else {
            Node *next = this->tail;

            for (size_t i = Size - 1; i > index + 1; --i) {
                next = next->prev;
            }

            Node *newNode = new Node(data, next->prev, next);
            next->prev->next = newNode;
            next->prev = newNode;
        }
    }
    ++Size;
}

template<typename T>
void List<T>::remove(size_t index) {
    if (index < 0 || index > Size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    if (index == 0) {
        pop_front();
    } else if (index == Size - 1) {
        pop_back();
    } else {
        if (index < Size / 2 + 1) {
            Node *previous = this->head;

            for (size_t i = 0; i < index - 1; ++i) {
                previous = previous->next;
            }

            Node *toDelete = previous->next;
            previous->next = toDelete->next;
            toDelete->next->prev = previous;

            delete toDelete;
        } else {
            Node *next = this->tail;

            for (size_t i = Size - 1; i > index + 1; --i) {
                next = next->prev;
            }

            Node *toDelete = next->prev;
            next->prev = toDelete->prev;
            toDelete->prev->next = next;

            delete toDelete;
        }
    }
    --Size;
}

template<typename T>
bool List<T>::isEmpty() const {
    return !Size;
}

template<typename T>
size_t List<T>::getSize() const {
    return Size;
}

template<typename T>
T &List<T>::operator[](const size_t &index) {
    if (index < 0 || index > Size - 1) {
        throw std::out_of_range("Index doesn't exist!");
    }

    Node *current;
    if (index < Size / 2 + 1) {
        current = this->head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = this->tail;
        for (size_t i = Size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current->data;
}

template<typename T>
void List<T>::show() const {
    Node *current = this->head;
    while (current) {
        std::cout << current->data << std::endl;
        current = current->next;
    }
}

template<typename T>
size_t List<T>::find(const T &rhs) const {
    size_t counter = 0;
    Node *current = this->head;
    while (current) {
        if (current->data == rhs) {
            return counter;
        }
        current = current->next;
        ++counter;
    }
    return -1;
}