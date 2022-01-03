#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

namespace simple {

template <typename T>
struct list_Node {
    list_Node() = default;

    list_Node(const T &value, list_Node *ptrPrev, list_Node *ptrNext) {
        m_data = new T(value);
        m_nextNode = ptrNext;
        m_prevNode = ptrPrev;
    }

    list_Node(T &&value, list_Node *ptrPrev, list_Node *ptrNext) {
        m_data = new T(std::move(value));
        m_nextNode = ptrNext;
        m_prevNode = ptrPrev;
    }

    ~list_Node(){
        delete m_data;
    }

    T *m_data;
    list_Node *m_nextNode{};
    list_Node *m_prevNode{};
};

template <typename T>
class LinkedListIterator {
public:
    LinkedListIterator() : m_Node() {}

    explicit LinkedListIterator(list_Node<T> *ptr) : m_Node(ptr){};

    LinkedListIterator &operator++() {
        m_Node = m_Node->m_nextNode;
        return *this;
    }

    LinkedListIterator operator++(int) {
        LinkedListIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    LinkedListIterator &operator+(int i) {
        while (i) {
            (*this)++;
            i--;
        }
        return *this;
    }

    T &operator[](int index) {
        auto tmp = m_Node;
        while (index) {
            tmp = tmp->m_nextNode;
            index--;
        }
        return *tmp->m_data;
    }

    T *operator->() const { return m_Node->m_data; }

    T &operator*() const { return *m_Node->m_data; }

    bool operator==(const LinkedListIterator &other) const {
        return m_Node == other.m_Node;
    }

    bool operator!=(const LinkedListIterator &other) const {
        return this->m_Node != other.m_Node;
    }

private:
    list_Node<T> *m_Node;
};

template <typename T>
class LinkedList {
private:
    typedef list_Node<T> m_Node;

public:
    typedef LinkedListIterator<T> iterator;

public:
    LinkedList() = default;

    LinkedList(const LinkedList<T> &other) {
        for (size_t i = 0; i < other.size(); i++) {
            this->emplaceBack(other[i]);
        }
    }

    LinkedList(LinkedList<T> &&other) noexcept {
        this->m_head = other.m_head;
        this->m_tail = other.m_tail;
        this->m_size = other.m_size;
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    ~LinkedList() {
        while (m_head) {
            auto tmp = m_head;
            m_head = m_head->m_nextNode;
            delete tmp;
        }
    }

    LinkedList<T> &operator=(LinkedList<T> &&other) {
        this->m_head = other.m_head;
        this->m_tail = other.m_tail;
        this->m_size = other.m_size;
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    LinkedList<T> &operator=(const LinkedList<T> &other) {
        for (size_t i = 0; i < other.size(); i++) {
            this->emplaceBack(other[i]);
        }
    }

    void pushBack(const T &element) {
        auto newElement = new m_Node(element, nullptr, nullptr);

        if (!m_head)
            m_head = newElement, m_tail = newElement;
        else {
            m_tail->m_nextNode = newElement;
            newElement->m_prevNode = m_tail;
            m_tail = newElement;
        }
        m_size++;
    }

    void pushBack(T &&element) {
        auto newElement = new m_Node(std::move(element), nullptr, nullptr);

        if (!m_head)
            m_head = newElement, m_tail = newElement;
        else {
            m_tail->m_nextNode = newElement;
            newElement->m_prevNode = m_tail;
            m_tail = newElement;
        }
        m_size++;
    }

    template <typename... Args>
    T &emplaceBack(Args &&...args) {
        auto newElement =
            new m_Node(T(std::forward<Args>(args)...), nullptr, nullptr);

        if (!m_head)
            m_head = newElement, m_tail = newElement;
        else {
            m_tail->m_nextNode = newElement;
            newElement->m_prevNode = m_tail;
            m_tail = newElement;
        }
        m_size++;
        return *newElement->m_data;
    }

    void pushFront(const T &element) {
        auto newElement = new m_Node(element, nullptr, m_head);
        m_head->m_prevNode = newElement;
        m_head = newElement;
        m_size++;
    }

    void pushFront(T &&element) {
        auto newElement = new m_Node(element, nullptr, m_head);
        m_head->m_prevNode = newElement;
        m_head = newElement;
        m_size++;
    }

    void popBack() {
        if (m_tail) {
            if (m_head == m_tail) {
                delete m_tail;
                m_head = nullptr;
                m_tail = nullptr;
            } else {
                auto tmp = m_tail->m_prevNode;
                delete m_tail;
                m_tail = tmp;
                if (tmp) m_tail->m_nextNode = nullptr;
            }
            m_size--;
        }
    }

    void popFront() {
        if (m_head) {
            if (m_head == m_tail) {
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
            } else {
                auto tmp = m_head->m_nextNode;
                delete m_head;
                m_head = tmp;
                if (tmp) m_head->m_prevNode = nullptr;
            }
            m_size--;
        }
    }

    void clear() {
        while (m_head) {
            auto tmp = m_head;
            m_head = m_head->m_nextNode;
            delete tmp;
        }
        m_size = 0;
    }

    T &operator[](size_t index) {
        auto tmp = m_head;
        while (index) {
            tmp = tmp->m_nextNode;
            index--;
        }
        return tmp->m_data;
    }

    const T &operator[](size_t index) const {
        auto tmp = m_head;
        while (index) {
            tmp = tmp->m_nextNode;
            index--;
        }
        return *tmp->m_data;
    }

    size_t size() const { return m_size; }

    bool empty() const { return m_size == 0; }

    const T &back() const { return *m_tail->m_data; }

    T &back() { return *m_tail->m_data; }

    T *find(const T &val) {
        auto tmp = m_head;
        while (tmp->m_nextNode) {
            if (*tmp->m_data == val) {
                return tmp->m_data;
            }
            tmp = tmp->m_nextNode;
        }
        return nullptr;
    }

public:
    iterator begin() { return iterator(m_head); }

    iterator end() { return iterator(nullptr); }

private:
    size_t m_size{};
    list_Node<T> *m_head{};
    list_Node<T> *m_tail{};
};
}  // namespace simple
#endif  // LINKEDLIST_H
