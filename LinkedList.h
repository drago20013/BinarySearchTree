/**
 * @file LinkedList.h
 * @author Michal Smaluch (https://github.com/drago20013)
 * @brief template header file for linked list data structure, not finished
 * @version 1.1
 * @date 2022-01-05
 *
 * @copyright GNU Public License v3.0
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

//! Simple implementations of data structures
namespace simple {
    //! Linked list node struct.

    //! Defines node of linked list with pointers to next and previous node.
    template<typename T>
    struct list_Node {
        //! Default constructor.
        list_Node() = default;

        //! Three argument constructor.

        //! Accepts data by reference and pointers to next and previous node.
        //! @param value Data to store in node.
        //! @param ptrPrev Pointer to previous node.
        //! @param ptrNext Pointer to next node.
        list_Node(const T &value, list_Node *ptrPrev, list_Node *ptrNext) {
            m_data = new T(value);
            m_nextNode = ptrNext;
            m_prevNode = ptrPrev;
        }

        //! Three argument constructor.

        //! Accepts data by right value reference (moves it) and pointers to next and previous node.
        //! @param value Data to store in node.
        //! @param ptrPrev Pointer to previous node.
        //! @param ptrNext Pointer to next node.
        list_Node(T &&value, list_Node *ptrPrev, list_Node *ptrNext) {
            m_data = new T(std::move(value));
            m_nextNode = ptrNext;
            m_prevNode = ptrPrev;
        }

        //! Destructor, deletes data in node.
        ~list_Node() {
            delete m_data;
        }

        T *m_data; //!< Pointer to data.
        list_Node *m_nextNode{}; //!< Pointer to next node.
        list_Node *m_prevNode{}; //!< Pointer to previous node.
    };

    //! Linked list forward iterator class.
    template<typename T>
    class LinkedListIterator {
    public:
        //! Default constructor.
        LinkedListIterator() : m_Node() {}

        //! One argument constructor.
        
        //! Accepts pointer to a node and assign it to m_Node.
        //! @param ptr Pointer to node.
        explicit LinkedListIterator(list_Node<T> *ptr) : m_Node(ptr){};

        //! Preincrementation operator.
        
        //! Increments iterator to next position.
        //! @return New iterator.
        LinkedListIterator &operator++() {
            m_Node = m_Node->m_nextNode;
            return *this;
        }

        //! Postincrementation operator.
        
        //! Increments iterator but returns old one.
        //! @return Old iterator.
        LinkedListIterator operator++(int) {
            LinkedListIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        //! Incrementation operator.

        //! Increment iterator n times.
        //! @return New iterator.
        LinkedListIterator &operator+(int i) {
            while (i) {
                (*this)++;
                i--;
            }
            return *this;
        }

        //! [] operator for iterator.
        
        //! @param index Index of element starting from one which iterator is pointing at.
        //! @return Reference to element.
        T &operator[](int index) {
            auto tmp = m_Node;
            while (index) {
                tmp = tmp->m_nextNode;
                index--;
            }
            return *tmp->m_data;
        }

        //! Pointer operator.

        //! @return Pointer to T.
        T *operator->() const { return m_Node->m_data; }

        //! Dereference operator.

        //! @return Value of T.
        T &operator*() const { return *m_Node->m_data; }

        //! Compare operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are the same, false otherwise.
        bool operator==(const LinkedListIterator &other) const {
            return m_Node == other.m_Node;
        }

        //! Difference operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are different, false otherwise.
        bool operator!=(const LinkedListIterator &other) const {
            return this->m_Node != other.m_Node;
        }

    private:
        list_Node<T> *m_Node; //!< Pointer to node iterator is pointing at.
    };

    //! Lined list data structure class.
    template<typename T>
    class LinkedList {
    private:
        typedef list_Node<T> m_Node;

    public:
        typedef LinkedListIterator<T> iterator;

    public:
        //! Default constructor.
        LinkedList() = default;

        //! Copy constructor.
        
        //! @param other Linked list to copy. 
        LinkedList(const LinkedList<T> &other) {
            for (size_t i = 0; i < other.size(); i++) {
                this->emplaceBack(other[i]);
            }
        }

        //! Move constructor.
        
        //! @param other Linked list to move.
        LinkedList(LinkedList<T> &&other) noexcept {
            this->m_head = other.m_head;
            this->m_tail = other.m_tail;
            this->m_size = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        //! Destructor, clears memory.
        ~LinkedList() {
            while (m_head) {
                auto tmp = m_head;
                m_head = m_head->m_nextNode;
                delete tmp;
            }
        }

        //! Move operator.
        
        //! @param other Linked list to move.
        //! @return Linked list.
        LinkedList<T> &operator=(LinkedList<T> &&other) {
            if (this != &other) {
                this->m_head = other.m_head;
                this->m_tail = other.m_tail;
                this->m_size = other.m_size;
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        //! Copy operator.
        
        //! @param other Linked list to copy.
        //! @return Linked list.
        LinkedList<T> &operator=(const LinkedList<T> &other) {
            if (this != &other) {
                for (size_t i = 0; i < other.size(); i++) {
                    this->emplaceBack(other[i]);
                }
            }
            return *this;
        }

        //! Push back function.
        
        //! Creates new node and place it at the end of list.
        //! @param element Element to push back.
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

        //! Push back function. (move)
        
        //! Creates new node and place it at the end of list.
        //! @param element Element to push back.
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

        //! Emplace back function.
        
        //! Creates element of T and then new node and place it at the end of list.
        //! @param args Arguments.
        //! @return Reference to created object.
        template<typename... Args>
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

        //! Push front function.
        
        //! Creates new node and place it at the beginning of list.
        //! @param element Element to push front.
        void pushFront(const T &element) {
            auto newElement = new m_Node(element, nullptr, m_head);
            m_head->m_prevNode = newElement;
            m_head = newElement;
            m_size++;
        }

        //! Push front function. (move)
        
        //! Creates new node and place it at the beginning of list.
        //! @param element Element to push front.
        void pushFront(T &&element) {
            auto newElement = new m_Node(element, nullptr, m_head);
            m_head->m_prevNode = newElement;
            m_head = newElement;
            m_size++;
        }

        //! Pop back function.
        
        //! Deletes last element in the list.
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

        //! Pop front function.
        
        //! Deletes first element in the list.
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

        //! Deletes all elements in a list.
        void clear() {
            while (m_head) {
                auto tmp = m_head;
                m_head = m_head->m_nextNode;
                delete tmp;
            }
            m_size = 0;
        }

        //! [] operator returns reference to element a given index.
        
        //! @param index Index of the element.
        //! @return Reference to an element.
        T &operator[](size_t index) {
            auto tmp = m_head;
            while (index) {
                tmp = tmp->m_nextNode;
                index--;
            }
            return tmp->m_data;
        }

        //! [] operator returns reference to element a given index. Const version.
        
        //! @param index Index of the element.
        //! @return Reference to an element.
        const T &operator[](size_t index) const {
            auto tmp = m_head;
            while (index) {
                tmp = tmp->m_nextNode;
                index--;
            }
            return *tmp->m_data;
        }

        //! Returns size of list.
        
        //! @return Number of elements.
        size_t size() const { return m_size; }

        //! True if empty.
        
        //! @return True if empty.
        bool empty() const { return m_size == 0; }

        //! Returns reference to last element. Const version.
        
        //! @return Reference to last element.
        const T &back() const { return *m_tail->m_data; }

        //! Returns pointer to last node in list. Const version.
        
        //! @return Pointer to last node in list.
        const list_Node<T> *ptrBack() const { return m_tail; }

        //! Returns pointer to last node in list.

        //! @return Pointer to last node in list.
        list_Node<T> *ptrBack() { return m_tail; }

        //! Returns reference to last element.

        //! @return Reference to last element.
        T &back() { return *m_tail->m_data; }

        //! Search for element in the list.
        
        //! @param val Element to search.
        //! @return Pointer to found element.
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
        //! Begin iterator.
        iterator begin() { return iterator(m_head); }

        //! End iterator.
        iterator end() { return iterator(nullptr); }

    private:
        size_t m_size{};//!< Size of list.
        list_Node<T> *m_head{}; //!< Pointer to the head of list.
        list_Node<T> *m_tail{}; //!< Pointer to tail of list.
    };
}// namespace simple
#endif// LINKEDLIST_H
