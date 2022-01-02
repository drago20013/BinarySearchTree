#ifndef BST_H
#define BST_H
// BST class

#include <iostream>

#include "LinkedList.h"

namespace simple {
template <typename T>
struct Node {
    Node() = default;

    Node(const T& value, Node* ptrParent, Node* ptrLeft, Node* ptrRight) {
        m_data = new T(value);
        m_parent = ptrParent;
        m_leftNode = ptrLeft;
        m_rightNode = ptrRight;
    }

    Node(T&& value, Node* ptrParent, Node* ptrLeft, Node* ptrRight) {
        m_data = new T(std::move(value));
        m_parent = ptrParent;
        m_leftNode = ptrLeft;
        m_rightNode = ptrRight;
    }

    ~Node() { delete m_data; }

    T* m_data;
    Node* m_parent;
    Node* m_leftNode;
    Node* m_rightNode;
};

template <typename T>
class BinarySearchTreeIterator {
public:
    BinarySearchTreeIterator() = default;

    explicit BinarySearchTreeIterator(Node<T>* ptrRoot, Node<T>* ptrNode) {
        m_ptrNode = ptrNode;
        Node<T>* curr = ptrRoot;
        while (curr) {
            m_ptrsStack.pushBack(curr);
            curr = curr->m_leftNode;
        }
    }

    BinarySearchTreeIterator& operator++() {
        Node<T>* curr = m_ptrsStack.back()->m_rightNode;
        m_ptrsStack.popBack();
        while (curr) {
            m_ptrsStack.pushBack(curr);
            curr = curr->m_leftNode;
        }
        m_ptrNode = m_ptrsStack.back();
        return *this;
    }

    BinarySearchTreeIterator operator++(int) {
        BinarySearchTreeIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    BinarySearchTreeIterator& operator+(size_t i) {
        while (i) {
            (*this)++;
            i--;
        }
        return *this;
    }

    T& operator[](size_t index) {
        (*this) + index;
        return *m_ptrsStack.back()->m_data;
    }

    T& operator*() const { return *m_ptrNode->m_data; }

    T* operator->() const { return m_ptrNode->m_data; }

    bool operator==(const BinarySearchTreeIterator& other) const {
        return m_ptrNode == other.m_ptrNode;
    }

    bool operator!=(const BinarySearchTreeIterator& other) const {
        return m_ptrNode != other.m_ptrNode;
    }

private:
    Node<T>* m_ptrNode;
    forwardList<Node<T>*>
        m_ptrsStack;  // was forward written by me, afer making
    // it bidirectional, I used it as stack
};

template <typename T>
class BinarySearchTree {
private:
    typedef Node<T> m_Node;

public:
    typedef BinarySearchTreeIterator<T> iterator;

public:
    BinarySearchTree() = default;

    // Copy/Move constructors/operators and emplace

    iterator insert(const T& data) {
        return insert(&m_rootNode, m_rootNode, data);
    }

    iterator insert(T&& data) {
        return insert(&m_rootNode, m_rootNode, std::move(data));
    }

    void inorder() const { inorder(m_rootNode); }

    iterator remove(const T& data) { return remove(search(m_rootNode, data)); }

    iterator search(const T& data) const {
        return iterator(m_rootNode, search(m_rootNode, data));
    }

    iterator getRoot() const { return iterator(m_rootNode, m_rootNode); }

    size_t getSize() const { return m_numOfElements; }

    iterator min() const { return iterator(m_rootNode, min(m_rootNode)); }

    iterator max() const { return iterator(m_rootNode, max(m_rootNode)); }

    const T& operator[](size_t index) const {
        auto it = min();
        it + index;
        return *it;
    }

    T& operator[](size_t index) {
        auto it = min();
        it + index;
        return *it;
    }

    ~BinarySearchTree() {
        if (m_rootNode) {
            clear(m_rootNode);
        }
    }

public:
    iterator begin() { return min(); }

    iterator end() { return iterator(m_rootNode, nullptr); }

private:
    iterator remove(m_Node* root) {
        if (!root) return iterator(m_rootNode, nullptr);

        // If no child is present
        if (!root->m_leftNode && !root->m_rightNode) {
            auto tmpParent = root->m_parent;
            if (root == tmpParent->m_leftNode)
                tmpParent->m_leftNode = nullptr;
            else
                tmpParent->m_rightNode = nullptr;

            delete root;
            return iterator(m_rootNode, tmpParent);
        }
        // If one child is present
        else if (!root->m_leftNode) {
            m_Node* tmpChild = root->m_rightNode;
            m_Node* tmpParent = root->m_parent;
            tmpChild->m_parent = tmpParent;
            if (tmpParent) {
                if (root == tmpParent->m_leftNode)
                    tmpParent->m_leftNode = tmpChild;
                else
                    tmpParent->m_rightNode = tmpChild;
            }
            delete root;
            return iterator(m_rootNode, tmpChild);
        } else if (!root->m_rightNode) {
            m_Node* tmpChild = root->m_leftNode;
            m_Node* tmpParent = root->m_parent;
            tmpChild->m_parent = tmpParent;
            if (tmpParent) {
                if (root == tmpParent->m_leftNode)
                    tmpParent->m_leftNode = tmpChild;
                else
                    tmpParent->m_rightNode = tmpChild;
            }
            delete root;
            return iterator(m_rootNode, tmpChild);
        }

        // If both children are present
        else {
            auto succ = successor(root);
            auto successorsParent = succ->m_parent;

            if (successorsParent != root)
                successorsParent->m_leftNode = succ->m_rightNode;
            else
                successorsParent->m_rightNode = succ->m_rightNode;

            *root->m_data = *succ->m_data;
            delete succ;
            return iterator(m_rootNode, root);
        }
    }

    void inorder(m_Node* root) const {
        if (root) {
            inorder(root->m_leftNode);
            std::cout << *root->m_data << " ";
            inorder(root->m_rightNode);
        }
    }

    m_Node* predecessor(m_Node* root) {
        if (root->m_leftNode) return max(root->m_leftNode);
        auto tmpParent = root->m_parent;
        while (tmpParent && root == tmpParent->m_leftNode) {
            tmpParent = tmpParent->m_parent;
        }
        return tmpParent;
    }

    m_Node* successor(m_Node* root) {
        if (root->m_rightNode) return min(root->m_rightNode);
        auto tmpParent = root->m_parent;
        while (tmpParent && root == tmpParent->m_rightNode) {
            tmpParent = tmpParent->m_parent;
        }
        return tmpParent;
    }

    m_Node* min(m_Node* root) const {
        auto tmp = root;
        while (tmp->m_leftNode) {
            tmp = tmp->m_leftNode;
        }
        return tmp;
    }

    m_Node* max(m_Node* root) const {
        auto tmp = root;
        while (tmp->m_rightNode) {
            tmp = tmp->m_rightNode;
        }
        return tmp;
    }

    void clear(m_Node* root) {
        auto tmp = root;
        if (tmp) {
            clear(tmp->m_leftNode);
            clear(tmp->m_rightNode);
            delete tmp;
        }
    }

    iterator insert(m_Node** rootPtr, m_Node* parentPtr, const T& data) {
        auto root = *rootPtr;
        if (!root) {
            *rootPtr = new m_Node(data, parentPtr, nullptr, nullptr);
            m_numOfElements++;
            return iterator(m_rootNode, *rootPtr);
        }

        if (data == *root->m_data) {
            // do nothing and return pointer to element
            return iterator(m_rootNode, root);
        }

        if (data < *root->m_data) {
            return insert(&(root->m_leftNode), root, data);
        } else {
            return insert(&(root->m_rightNode), root, data);
        }
    }

    iterator insert(m_Node** rootPtr, m_Node* parentPtr, T&& data) {
        auto root = *rootPtr;
        if (!root) {
            *rootPtr = new m_Node(std::move(data), parentPtr, nullptr, nullptr);
            m_numOfElements++;
            return iterator(m_rootNode, *rootPtr);
        }

        if (data == *root->m_data) {
            // do nothing and return pointer to element
            return iterator(m_rootNode, root);
        }

        if (data < *root->m_data) {
            return insert(&(root->m_leftNode), root, std::move(data));
        } else {
            return insert(&(root->m_rightNode), root, std::move(data));
        }
    }

    m_Node* search(m_Node* root, const T& data) const {
        if (!root) return nullptr;

        if (data == *root->m_data) return root;

        if (data < *root->m_data)
            return search(root->m_leftNode, data);
        else
            return search(root->m_rightNode, data);
    }

private:
    size_t m_numOfElements{};
    m_Node* m_rootNode{};
};

}  // namespace simple
#endif  // BST_H
