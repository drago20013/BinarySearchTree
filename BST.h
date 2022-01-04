#ifndef BST_H
#define BST_H
// BST class

#include <fstream>
#include <iostream>

#include "LinkedList.h"

namespace simple {
    template<typename T>
    struct Node {
        Node() = default;

        Node(const T &value, Node *ptrParent, Node *ptrLeft, Node *ptrRight) {
            m_data = new T(value);
            m_parent = ptrParent;
            m_leftNode = ptrLeft;
            m_rightNode = ptrRight;
        }

        Node(T &&value, Node *ptrParent, Node *ptrLeft, Node *ptrRight) {
            m_data = new T(std::move(value));
            m_parent = ptrParent;
            m_leftNode = ptrLeft;
            m_rightNode = ptrRight;
        }

        ~Node() { delete m_data; }

        T *m_data;
        Node *m_parent;
        Node *m_leftNode;
        Node *m_rightNode;
    };

    template<typename T>
    class BinarySearchTreeIterator {
    public:
        BinarySearchTreeIterator() = default;

        explicit BinarySearchTreeIterator(Node<T> *ptrRoot) {
            Node<T> *curr = ptrRoot;
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_leftNode;
            }
        }

        BinarySearchTreeIterator(const BinarySearchTreeIterator &other) {
            m_ptrsStack = other.m_ptrsStack;
        }

        BinarySearchTreeIterator(BinarySearchTreeIterator &&other) noexcept {
            m_ptrsStack.clear();
            m_ptrsStack = std::move(other.m_ptrsStack);
        }

        BinarySearchTreeIterator &operator=(BinarySearchTreeIterator &&other) noexcept {
            if (this != &other) {
                m_ptrsStack.clear();
                m_ptrsStack = std::move(other.m_ptrsStack);
            }
            return *this;
        }

        BinarySearchTreeIterator &operator=(const BinarySearchTreeIterator &other) {
            if (this != &other) {
                m_ptrsStack = other.m_ptrsStack;
            }
            return *this;
        }

        BinarySearchTreeIterator &operator++() {
            Node<T> *curr = m_ptrsStack.back()->m_rightNode;
            m_ptrsStack.popBack();
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_leftNode;
            }
            return *this;
        }

        BinarySearchTreeIterator operator++(int) {
            const BinarySearchTreeIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        BinarySearchTreeIterator &operator+(size_t i) {
            while (i) {
                (*this)++;
                i--;
            }
            return *this;
        }

        const T &operator*() const { return *m_ptrsStack.back()->m_data; }

        const T *operator->() const { return m_ptrsStack.back()->m_data; }

        bool operator==(const BinarySearchTreeIterator &other) const {
            return m_ptrsStack.ptrBack() == other.m_ptrsStack.ptrBack();
        }

        bool operator!=(const BinarySearchTreeIterator &other) const {
            return m_ptrsStack.ptrBack() != other.m_ptrsStack.ptrBack();
        }

    private:
        LinkedList<Node<T> *>
                m_ptrsStack;//It was forward list written by me, after making
        // it bidirectional, I used it as "stack"
    };

    template<typename T>
    class BinarySearchTreeReverseIterator {
    public:
        BinarySearchTreeReverseIterator() = default;

        explicit BinarySearchTreeReverseIterator(Node<T> *ptrRoot) {
            Node<T> *curr = ptrRoot;
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_rightNode;
            }
        }

        BinarySearchTreeReverseIterator(const BinarySearchTreeReverseIterator &other) {
            m_ptrsStack = other.m_ptrsStack;
        }

        BinarySearchTreeReverseIterator(BinarySearchTreeReverseIterator &&other) noexcept {
            m_ptrsStack.clear();
            m_ptrsStack = std::move(other.m_ptrsStack);
        }

        BinarySearchTreeReverseIterator &operator=(BinarySearchTreeReverseIterator &&other) noexcept {
            if (this != &other) {
                m_ptrsStack.clear();
                m_ptrsStack = std::move(other.m_ptrsStack);
            }
            return *this;
        }

        BinarySearchTreeReverseIterator &operator=(const BinarySearchTreeReverseIterator &other) {
            if (this != &other) {
                m_ptrsStack = other.m_ptrsStack;
            }
            return *this;
        }

        BinarySearchTreeReverseIterator &operator++() {
            Node<T> *curr = m_ptrsStack.back()->m_leftNode;
            m_ptrsStack.popBack();
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_rightNode;
            }
            return *this;
        }

        BinarySearchTreeReverseIterator operator++(int) {
            const BinarySearchTreeReverseIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        BinarySearchTreeReverseIterator &operator+(size_t i) {
            while (i) {
                (*this)++;
                i--;
            }
            return *this;
        }

        const T &operator*() const { return *m_ptrsStack.back()->m_data; }

        const T *operator->() const { return m_ptrsStack.back()->m_data; }

        bool operator==(const BinarySearchTreeReverseIterator &other) const {
            return m_ptrsStack.ptrBack() == other.m_ptrsStack.ptrBack();
        }

        bool operator!=(const BinarySearchTreeReverseIterator &other) const {
            return m_ptrsStack.ptrBack() != other.m_ptrsStack.ptrBack();
        }

    private:
        LinkedList<Node<T> *>
                m_ptrsStack;//It was forward list written by me, after making
        // it bidirectional, I used it as "stack"
    };

    template<typename T>
    class BinarySearchTree {
    private:
        typedef Node<T> m_Node;

    public:
        typedef BinarySearchTreeIterator<T> iterator;
        typedef BinarySearchTreeReverseIterator<T> reverse_iterator;

    public:
        BinarySearchTree() = default;

        BinarySearchTree(const BinarySearchTree &other) {
            simple::LinkedList<T> res;
            save(other.m_rootNode, res);
            for (auto &e: res)
                insert(e);
        }

        BinarySearchTree(BinarySearchTree &&other) noexcept {
            m_rootNode = other.m_rootNode;
            m_numOfElements = other.m_numOfElements;
            other.m_rootNode = nullptr;
            other.m_numOfElements = 0;
        }

        BinarySearchTree(std::initializer_list<T> init) {
            for (auto &e: init)
                insert(e);
        }

        BinarySearchTree &operator=(const BinarySearchTree &other) {
            if (this != &other && other.m_rootNode) {
                LinkedList<T> res;
                save(other.m_rootNode, res);
                for (auto &e: res)
                    insert(e);
            }
            return *this;
        }

        BinarySearchTree &operator=(BinarySearchTree &&other) noexcept {
            if (this != &other) {
                m_rootNode = other.m_rootNode;
                m_numOfElements = other.m_numOfElements;
                other.m_rootNode = nullptr;
                other.m_numOfElements = 0;
            }
            return *this;
        }

        void serialize(const std::string &fileName) {
            std::ofstream oFile(fileName, std::ios::out | std::ios::binary);
            if (oFile) {
                oFile.write((char *) &m_numOfElements, sizeof(m_numOfElements));
                LinkedList<T> res;
                save(m_rootNode, res);
                for (const auto &e: res) {
                    oFile.write((char *) &e, sizeof(e));
                }
                oFile.close();
            }
        }

        void deserialize(const std::string &fileName) {
            std::ifstream iFile(fileName, std::ios::in | std::ios::binary);
            if (iFile) {
                size_t tmpSize;
                T tmp;
                iFile.read((char *) &tmpSize, sizeof(tmpSize));
                for (size_t i = 0; i < tmpSize; ++i) {
                    iFile.read((char *) &tmp, sizeof(tmp));
                    insert(tmp);
                }
                iFile.close();
            }
        }

        const T &insert(const T &data) {
            return *(insert(&m_rootNode, m_rootNode, data)->m_data);
        }

        const T &insert(T &&data) {
            return *(insert(&m_rootNode, m_rootNode, std::move(data))->m_data);
        }

        template<typename... Args>
        const T &emplace(Args &&...args) {
            return insert(T(std::forward<Args>(args)...));
        }

        void remove(const T &data) { remove(search(m_rootNode, data)); }

        void clear() {
            clear(m_rootNode);
            m_numOfElements = 0;
            m_rootNode = nullptr;
        }

        const T *search(const T &data) const {
            auto tmp = search(m_rootNode, data);
            return tmp ? tmp->m_data : nullptr;
        }

        const T &root() const { return *m_rootNode->m_data; }

        [[nodiscard]] size_t size() const { return m_numOfElements; }

        const T &min() const { return *(min(m_rootNode)->m_data); }

        const T &max() const { return *(max(m_rootNode)->m_data); }

        friend std::ofstream &operator<<(std::ofstream &os, const BinarySearchTree &source) {
            if (os.is_open() && source.m_rootNode) {
                simple::LinkedList<T> res;
                source.save(source.m_rootNode, res);
                for (auto &e: res)
                    os << e << "\n";
            }
            return os;
        }

        friend std::ifstream &operator>>(std::ifstream &is, BinarySearchTree &source) {
            if (is.is_open()) {
                T tmp;
                while (is >> tmp)
                    source.insert(tmp);
            }
            return is;
        }

        BinarySearchTree &operator<<(const T &data) {
            insert(data);
            return *this;
        }

        ~BinarySearchTree() {
            clear();
        }

    public:
        iterator begin() { return iterator(m_rootNode); }

        iterator end() { return iterator(nullptr); }

        reverse_iterator rbegin() { return reverse_iterator(m_rootNode); }

        reverse_iterator rend() { return reverse_iterator(nullptr); }

    private:
        void save(m_Node *root, LinkedList<T> &result) const {
            auto tmp = root;
            if (tmp) {
                result.pushBack(*tmp->m_data);
                save(tmp->m_leftNode, result);
                save(tmp->m_rightNode, result);
            }
        }

        void remove(m_Node *node) {
            if (!node) return;
            // If no child is present
            if (!node->m_leftNode && !node->m_rightNode) {
                auto tmpParent = node->m_parent;
                if (node == tmpParent->m_leftNode)
                    tmpParent->m_leftNode = nullptr;
                else
                    tmpParent->m_rightNode = nullptr;

                delete node;
                m_numOfElements--;
            }
            // If one child is present
            else if (!node->m_leftNode) {
                m_Node *tmpChild = node->m_rightNode;
                m_Node *tmpParent = node->m_parent;
                tmpChild->m_parent = tmpParent;
                if (tmpParent) {
                    if (node == tmpParent->m_leftNode)
                        tmpParent->m_leftNode = tmpChild;
                    else
                        tmpParent->m_rightNode = tmpChild;
                }
                delete node;
                m_numOfElements--;
            } else if (!node->m_rightNode) {
                m_Node *tmpChild = node->m_leftNode;
                m_Node *tmpParent = node->m_parent;
                tmpChild->m_parent = tmpParent;
                if (tmpParent) {
                    if (node == tmpParent->m_leftNode)
                        tmpParent->m_leftNode = tmpChild;
                    else
                        tmpParent->m_rightNode = tmpChild;
                }
                delete node;
                m_numOfElements--;
            }

            // If both children are present
            else {
                auto succ = successor(node);
                auto successorsParent = succ->m_parent;

                if (successorsParent != node)
                    successorsParent->m_leftNode = succ->m_rightNode;
                else
                    successorsParent->m_rightNode = succ->m_rightNode;

                *node->m_data = *succ->m_data;
                delete succ;
                m_numOfElements--;
            }
        }

        const m_Node *predecessor(m_Node *root) const {
            if (root->m_leftNode) return max(root->m_leftNode);
            auto tmpParent = root->m_parent;
            while (tmpParent && root == tmpParent->m_leftNode) {
                tmpParent = tmpParent->m_parent;
            }
            return tmpParent;
        }

        const m_Node *successor(m_Node *root) const {
            if (root->m_rightNode) return min(root->m_rightNode);
            auto tmpParent = root->m_parent;
            while (tmpParent && root == tmpParent->m_rightNode) {
                tmpParent = tmpParent->m_parent;
            }
            return tmpParent;
        }

        const m_Node *min(m_Node *root) const {
            if (root) {
                auto tmp = root;
                while (tmp->m_leftNode) {
                    tmp = tmp->m_leftNode;
                }
                return tmp;
            } else
                return nullptr;
        }

        const m_Node *max(m_Node *root) const {
            auto tmp = root;
            while (tmp->m_rightNode) {
                tmp = tmp->m_rightNode;
            }
            return tmp;
        }

        void clear(m_Node *root) {
            if (root) {
                clear(root->m_leftNode);
                clear(root->m_rightNode);
                delete root;
            }
        }

        const m_Node *insert(m_Node **rootPtr, m_Node *parentPtr, const T &data) {
            auto root = *rootPtr;
            if (!root) {
                *rootPtr = new m_Node(data, parentPtr, nullptr, nullptr);
                m_numOfElements++;
                return *rootPtr;
            }

            if (data == *root->m_data) {
                // do nothing and return pointer to element
                return root;
            }

            if (data < *root->m_data) {
                return insert(&(root->m_leftNode), root, data);
            } else {
                return insert(&(root->m_rightNode), root, data);
            }
        }

        const m_Node *insert(m_Node **rootPtr, m_Node *parentPtr, T &&data) {
            auto root = *rootPtr;
            if (!root) {
                *rootPtr = new m_Node(std::move(data), parentPtr, nullptr, nullptr);
                m_numOfElements++;
                return *rootPtr;
            }

            if (data == *root->m_data) {
                // do nothing and return pointer to element
                return root;
            }

            if (data < *root->m_data) {
                return insert(&(root->m_leftNode), root, std::move(data));
            } else {
                return insert(&(root->m_rightNode), root, std::move(data));
            }
        }

        m_Node *search(m_Node *root, const T &data) const {
            if (!root) return nullptr;

            if (data == *root->m_data) return root;

            if (data < *root->m_data)
                return search(root->m_leftNode, data);
            else
                return search(root->m_rightNode, data);
        }

    private:
        size_t m_numOfElements{};
        m_Node *m_rootNode{};
    };

}// namespace simple
#endif// BST_H