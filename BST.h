/**
 * @file BST.h
 * @author Michal Smaluch (https://github.com/drago20013)
 * @brief template header file for binary search tree data structure
 * @version 1.2
 * @date 2022-01-05
 *
 * @copyright GNU Public License v3.0
 */

#ifndef BST_H
#define BST_H
// BST class

#include <fstream>
#include <iostream>
#include <functional>

#include "LinkedList.h"

namespace simple {
    //! Binary search tree node struct.

    //! Defines node of binary search tree with pointers to parent, left and right child.
    template<typename T>
    struct Node {
        //! Default constructor.
        Node() = default;

        //! Four argument constructor.

        //! Accepts data by reference and pointers to parent, left/right children.
        //! @param value Data to store in node.
        //! @param ptrParent Pointer to parent node.
        //! @param ptrLeft Pointer to left child.
        //! @param ptrRight Pointer to right child.
        Node(const T &value, Node *ptrParent, Node *ptrLeft, Node *ptrRight) {
            m_data = new T(value);
            m_parent = ptrParent;
            m_leftNode = ptrLeft;
            m_rightNode = ptrRight;
        }

        //! Four argument constructor.

        //! Accepts data by as right value reference, moves it and pointers to parent, left/right children.
        //! @param value Data to store in node.
        //! @param ptrParent Pointer to parent node.
        //! @param ptrLeft Pointer to left child.
        //! @param ptrRight Pointer to right child.
        Node(T &&value, Node *ptrParent, Node *ptrLeft, Node *ptrRight) {
            m_data = new T(std::move(value));
            m_parent = ptrParent;
            m_leftNode = ptrLeft;
            m_rightNode = ptrRight;
        }

        //! Destructor of node, deletes data.
        ~Node() {
            delete m_data;
            m_parent = nullptr;
            m_leftNode = nullptr;
            m_rightNode = nullptr;
        }

        T *m_data;        //!< Pointer to stored data.
        Node *m_parent;   //!< Pointer to parent node.
        Node *m_leftNode; //!< Pointer to left child.
        Node *m_rightNode;//!< Pointer to right child.
    };

    //! Binary search tree forward iterator class.

    //! Iterator for binary search tree, it uses some container as "stack" to keep history of where it points.
    //! It is in order iterator, from min to max.
    template<typename T>
    class BinarySearchTreeIterator {
    public:
        //! Default constructor for forward iterator.
        BinarySearchTreeIterator() = default;

        //! One argument constructor.

        //! Accepts pointer to root node of a tree, then initialize a stack.
        //! @param ptrRoot Pointer to a root of tree.
        explicit BinarySearchTreeIterator(Node<T> *ptrRoot) {
            Node<T> *curr = ptrRoot;
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_leftNode;
            }
        }

        //! Copy constructor for forward iterator.
        BinarySearchTreeIterator(const BinarySearchTreeIterator &other) {
            m_ptrsStack = other.m_ptrsStack;
        }

        //! Move constructor for forward iterator.
        BinarySearchTreeIterator(BinarySearchTreeIterator &&other) noexcept {
            m_ptrsStack.clear();
            m_ptrsStack = std::move(other.m_ptrsStack);
        }

        //! Move operator for forward iterator.

        //! @param other Other iterator to copy from.
        //! @return Iterator.
        BinarySearchTreeIterator &operator=(BinarySearchTreeIterator &&other) noexcept {
            if (this != &other) {
                m_ptrsStack.clear();
                m_ptrsStack = std::move(other.m_ptrsStack);
            }
            return *this;
        }

        //! Copy operator for forward iterator.

        //! @param other Other iterator to move.
        //! @return Iterator.
        BinarySearchTreeIterator &operator=(const BinarySearchTreeIterator &other) {
            if (this != &other) {
                m_ptrsStack = other.m_ptrsStack;
            }
            return *this;
        }

        //! Pre-incrementation operator.

        //! Increment iterator to next place.
        //! @return New iterator.
        BinarySearchTreeIterator &operator++() {
            Node<T> *curr = m_ptrsStack.back()->m_rightNode;
            m_ptrsStack.popBack();
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_leftNode;
            }
            return *this;
        }

        //! Post-incrementation operator.

        //! Increment iterator to next place.
        //! @return Old iterator.
        BinarySearchTreeIterator operator++(int) {
            const BinarySearchTreeIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        //! Incrementation operator.

        //! Increment iterator n times.
        //! @return New iterator.
        BinarySearchTreeIterator &operator+(size_t i) {
            while (i) {
                (*this)++;
                i--;
            }
            return *this;
        }

        //! Dereference operator.

        //! @return Value of T.
        const T &operator*() const { return *m_ptrsStack.back()->m_data; }

        //! Pointer operator.

        //! @return Pointer to T.
        const T *operator->() const { return m_ptrsStack.back()->m_data; }

        //! Compare operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are the same, false otherwise.
        bool operator==(const BinarySearchTreeIterator &other) const {
            return m_ptrsStack.ptrBack() == other.m_ptrsStack.ptrBack();
        }

        //! Difference operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are different, false otherwise.
        bool operator!=(const BinarySearchTreeIterator &other) const {
            return m_ptrsStack.ptrBack() != other.m_ptrsStack.ptrBack();
        }

    private:
        LinkedList<Node<T> *>
                m_ptrsStack;//!< LinkedList used as stack, needed in iterator.
        //It was forward list written by me, after making
        // it bidirectional, I used it as "stack"
    };

    //! Binary search tree reverse iterator class.

    //! Iterator for binary search tree, it uses some container as "stack" to keep history where it points.
    //! It is in order iterator, from max to min.
    template<typename T>
    class BinarySearchTreeReverseIterator {
    public:
        //! Default constructor for reverse iterator.
        BinarySearchTreeReverseIterator() = default;

        //! One argument constructor.

        //! Accepts pointer to root node of a tree, then initialize a stack.
        //! @param ptrRoot Pointer to a root of tree.
        explicit BinarySearchTreeReverseIterator(Node<T> *ptrRoot) {
            Node<T> *curr = ptrRoot;
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_rightNode;
            }
        }

        //! Copy constructor for reverse iterator.
        BinarySearchTreeReverseIterator(const BinarySearchTreeReverseIterator &other) {
            m_ptrsStack = other.m_ptrsStack;
        }

        //! Move constructor for reverse iterator.
        BinarySearchTreeReverseIterator(BinarySearchTreeReverseIterator &&other) noexcept {
            m_ptrsStack.clear();
            m_ptrsStack = std::move(other.m_ptrsStack);
        }

        //! Move operator for reverse iterator.

        //! @param other Other iterator to copy from.
        //! @return Iterator.
        BinarySearchTreeReverseIterator &operator=(BinarySearchTreeReverseIterator &&other) noexcept {
            if (this != &other) {
                m_ptrsStack.clear();
                m_ptrsStack = std::move(other.m_ptrsStack);
            }
            return *this;
        }

        //! Copy operator for reverse iterator.

        //! @param other Other iterator to move.
        //! @return Iterator.
        BinarySearchTreeReverseIterator &operator=(const BinarySearchTreeReverseIterator &other) {
            if (this != &other) {
                m_ptrsStack = other.m_ptrsStack;
            }
            return *this;
        }

        //! Pre-incrementation operator.

        //! Increment iterator to next place.
        //! @return New iterator.
        BinarySearchTreeReverseIterator &operator++() {
            Node<T> *curr = m_ptrsStack.back()->m_leftNode;
            m_ptrsStack.popBack();
            while (curr) {
                m_ptrsStack.pushBack(curr);
                curr = curr->m_rightNode;
            }
            return *this;
        }

        //! Post-incrementation operator.

        //! Increment iterator to next place.
        //! @return Old iterator.
        BinarySearchTreeReverseIterator operator++(int) {
            const BinarySearchTreeReverseIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        //! Incrementation operator.

        //! Increment iterator n times.
        //! @return New iterator.
        BinarySearchTreeReverseIterator &operator+(size_t i) {
            while (i) {
                (*this)++;
                i--;
            }
            return *this;
        }

        //! Dereference operator.

        //! @return Value of T.
        const T &operator*() const { return *m_ptrsStack.back()->m_data; }

        //! Pointer operator.

        //! @return Pointer to T.
        const T *operator->() const { return m_ptrsStack.back()->m_data; }

        //! Compare operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are the same, false otherwise.
        bool operator==(const BinarySearchTreeReverseIterator &other) const {
            return m_ptrsStack.ptrBack() == other.m_ptrsStack.ptrBack();
        }

        //! Difference operator.

        //! @param other Iterator to compare with.
        //! @return True if iterators are different, false otherwise.
        bool operator!=(const BinarySearchTreeReverseIterator &other) const {
            return m_ptrsStack.ptrBack() != other.m_ptrsStack.ptrBack();
        }

    private:
        LinkedList<Node<T> *>
                m_ptrsStack;//!< LinkedList used as stack, needed in iterator.
        // It was forward list written by me, after making
        // it bidirectional, I used it as "stack"
    };

    //! Binary search tree class.

    //! Stores pointer to root and number of nodes.
    template<typename T>
    class BinarySearchTree {
    private:
        typedef Node<T> m_Node;

    public:
        typedef BinarySearchTreeIterator<T> iterator;
        typedef BinarySearchTreeReverseIterator<T> reverse_iterator;

    public:
        //! Default constructor.

        //! @param compFunc Comparison function.
        explicit BinarySearchTree(std::function<bool(const T &a, const T &b)> compFunc = [](const T &a, const T &b) { return a < b; }) : m_compFunc(compFunc){};

        //! Copy constructor.

        //! @param other Binary search tree to copy.
        BinarySearchTree(const BinarySearchTree &other) {
            simple::LinkedList<T> res;
            save(other.m_rootNode, res);
            for (auto &e: res)
                insert(e);

            m_compFunc = other.m_compFunc;
        }

        //! Move constructor.

        //! @param other Binary search tree to move.
        BinarySearchTree(BinarySearchTree &&other) noexcept {
            m_rootNode = other.m_rootNode;
            m_numOfElements = other.m_numOfElements;
            m_compFunc = std::move(other.m_compFunc);
            other.m_rootNode = {};
            other.m_numOfElements = {};
            other.m_compFunc = {};
        }

        //! Initializer list constructor.

        //! @param init Initializer list.
        //! @param compFunc Comparison function.
        BinarySearchTree(
                std::initializer_list<T> init, std::function<bool(const T &a, const T &b)> compFunc = [](const T &a, const T &b) { return a < b; }) : m_compFunc(compFunc) {
            for (auto &e: init)
                insert(e);
        }

        //! Copy operator.

        //! @param other Binary search tree to copy.
        //! @return Binary search tree.
        BinarySearchTree &operator=(const BinarySearchTree &other) {
            if (this != &other && other.m_rootNode) {
                LinkedList<T> res;
                save(other.m_rootNode, res);
                for (auto &e: res)
                    insert(e);

                m_compFunc = other.m_compFunc;
            }
            return *this;
        }

        //! Move operator.

        //! @param other Binary search tree to move.
        //! @return Binary search tree.
        BinarySearchTree &operator=(BinarySearchTree &&other) noexcept {
            if (this != &other) {
                m_rootNode = other.m_rootNode;
                m_numOfElements = other.m_numOfElements;
                m_compFunc = std::move(other.m_compFunc);
                other.m_rootNode = {};
                other.m_numOfElements = {};
                other.m_compFunc = {};
            }
            return *this;
        }

        //! Serialize function.

        //! Writes binary search tree in binary format to file.
        //! @param fileName Name of file to save data to.
        void serialize(const std::string &fileName) {
            std::ofstream oFile(fileName, std::ios::out | std::ios::binary);
            if (oFile) {
                oFile.write(reinterpret_cast<char *>(&m_numOfElements), sizeof(m_numOfElements));
                LinkedList<T> res;
                save(m_rootNode, res);
                for (auto &e: res) {
                    oFile.write(reinterpret_cast<char *>(&e), sizeof(e));
                }
                oFile.close();
            }
        }

        //! Deserialize function.

        //! Reads binary data from file and fills binary search tree.
        //! @param fileName Name of file to read from.
        void deserialize(const std::string &fileName) {
            std::ifstream iFile(fileName, std::ios::in | std::ios::binary);
            if (iFile) {
                size_t tmpSize;
                T tmp;
                iFile.read(reinterpret_cast<char *>(&tmpSize), sizeof(tmpSize));
                for (size_t i = 0; i < tmpSize; ++i) {
                    iFile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
                    insert(tmp);
                }
                iFile.close();
            }
        }

        //! Inserts data to binary search tree.

        //! @param data Data.
        //! @return Reference to data.
        const T &insert(const T &data) {
            return *(insert(&m_rootNode, m_rootNode, data)->m_data);
        }

        //! Inserts data to binary search tree. (moves)

        //! @param data Data.
        //! @return Reference to data.
        const T &insert(T &&data) {
            return *(insert(&m_rootNode, m_rootNode, std::move(data))->m_data);
        }

        //! Emplace data to binary search tree. (moves)

        //! @param args argumets.
        //! @return Reference to emplaced object.
        template<typename... Args>
        const T &emplace(Args &&...args) {
            return insert(T(std::forward<Args>(args)...));
        }

        //! Removes data from binary search tree.

        //! @param data data to remove.
        void remove(const T &data) { remove(search(m_rootNode, data)); }

        //! Clears binary search tree.
        void clear() {
            clear(m_rootNode);
            m_numOfElements = 0;
            m_rootNode = nullptr;
        }

        //! Search for data.

        //! @param data Data to search for.
        //! @return Pointer to found object.
        const T *search(const T &data) const {
            auto tmp = search(m_rootNode, data);
            return tmp ? tmp->m_data : nullptr;
        }

        //! Returns reference to root object.

        //! @return Reference to root object.
        const T &root() const { return *m_rootNode->m_data; }

        //! Returns size of binary search tree.

        //! @return Number of elements in binary search tree.
        [[nodiscard]] size_t size() const { return m_numOfElements; }

        //! Returns reference to minimum object in binary search tree.

        //! @return Reference to minimum object in binary search tree.
        const T &min() const { return *(min(m_rootNode)->m_data); }

        //! Returns reference to maximum object in binary search tree.

        //! @return Reference to maximum object in binary search tree.
        const T &max() const { return *(max(m_rootNode)->m_data); }

        //! Output operator for file stream.

        //! Saves binary search tree in text format in file.
        //! @param os Output file stream.
        //! @param source Binary search tree to save.
        //! @return Output file stream.
        friend std::ofstream &operator<<(std::ofstream &os, const BinarySearchTree &source) {
            if (os.is_open() && source.m_rootNode) {
                simple::LinkedList<T> res;
                source.save(source.m_rootNode, res);
                for (auto &e: res)
                    os << e << "\n";
            }
            return os;
        }

        //! Input operator for file stream.

        //! Reads binary search tree in text format from file.
        //! @param is Input file stream.
        //! @param source Binary search tree to put data in.
        //! @return Input file stream.
        friend std::ifstream &operator>>(std::ifstream &is, BinarySearchTree &source) {
            if (is.is_open()) {
                T tmp;
                while (is >> tmp)
                    source.insert(tmp);
            }
            return is;
        }

        //! Output operator for adding data to binary search tree.

        //! @param data Data to insert.
        //! @return BinarySearchTree.
        BinarySearchTree &operator<<(const T &data) {
            insert(data);
            return *this;
        }

        //! Destructor.

        //! Calls clear() function which clears memory.
        ~BinarySearchTree() {
            clear();
        }

    public:
        //! Iterator to min element.

        //! @return begin iterator.
        iterator begin() { return iterator(m_rootNode); }

        //! Iterator to end. (nullptr)

        //! @return end iterator.
        iterator end() { return iterator(nullptr); }

        //! Reverse iterator to max element.

        //! @return rbegin iterator.
        reverse_iterator rbegin() { return reverse_iterator(m_rootNode); }

        //! Reverse iterator to end. (nullptr)

        //! @return rend iterator.
        reverse_iterator rend() { return reverse_iterator(nullptr); }

    private:
        //! Private save function.

        //! Stores content of binary search tree in order in LinkedList for further use.
        //! Uses recursion.
        //! @param root Pointer to local root.
        //! @param result LinkedList which result will be stored.
        void save(m_Node *root, LinkedList<T> &result) const {
            auto tmp = root;
            if (tmp) {
                result.pushBack(*tmp->m_data);
                save(tmp->m_leftNode, result);
                save(tmp->m_rightNode, result);
            }
        }

        //! Private remove function.

        //! If node exist deletes it.
        //! @param node Node to delete
        void remove(const m_Node *node) {
            if (!node) return;
            // If no child is present
            if (!node->m_leftNode && !node->m_rightNode) {
                auto tmpParent = node->m_parent;
                if (node == tmpParent->m_leftNode)
                    tmpParent->m_leftNode = nullptr;
                else
                    tmpParent->m_rightNode = nullptr;

                if (node == m_rootNode) {
                    delete node;
                    m_rootNode = nullptr;
                } else {
                    delete node;
                }
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
                if (node == m_rootNode) {
                    delete node;
                    m_rootNode = tmpChild;
                } else {
                    delete node;
                }
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
                if (node == m_rootNode) {
                    delete node;
                    m_rootNode = tmpChild;
                } else {
                    delete node;
                }
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

        //! Predecessor function.

        //! Returns predecessor of given node.
        //! @param root Local root node.
        //! @return Pointer to predecessor.
        const m_Node *predecessor(const m_Node *root) const {
            if (root->m_leftNode) return max(root->m_leftNode);
            auto tmpParent = root->m_parent;
            while (tmpParent && root == tmpParent->m_leftNode) {
                tmpParent = tmpParent->m_parent;
            }
            return tmpParent;
        }

        //! Successor function.

        //! Returns successor of given node.
        //! @param root Local root node.
        //! @return Pointer to successor.
        const m_Node *successor(const m_Node *root) const {
            if (root->m_rightNode) return min(root->m_rightNode);
            auto tmpParent = root->m_parent;
            while (tmpParent && root == tmpParent->m_rightNode) {
                tmpParent = tmpParent->m_parent;
            }
            return tmpParent;
        }

        //! Min function.

        //! Returns min node.
        //! @param root Local root.
        //! @return Min node if exist, nullptr otherwise.
        const m_Node *min(m_Node *root) const {
            auto tmp = root;
            while (tmp->m_leftNode) {
                tmp = tmp->m_leftNode;
            }
            return tmp;
        }

        //! Max function.

        //! Returns max node.
        //! @param root Local root.
        //! @return Max node if exist, nullptr otherwise.
        const m_Node *max(m_Node *root) const {
            auto tmp = root;
            while (tmp->m_rightNode) {
                tmp = tmp->m_rightNode;
            }
            return tmp;
        }

        //! Clear function.

        //! Clears memory from all object in binary search tree.
        //! @param root Local root.
        void clear(m_Node *root) {
            if (root) {
                clear(root->m_leftNode);
                clear(root->m_rightNode);
                delete root;
            }
        }

        //! Private insert function.

        //! Creates new node with provided data, inserts it in correct place.
        //! @param rootPtr Pointer to local root.
        //! @param parentPtr Pointer to a parent node.
        //! @param data Data to insert in node.
        //! @return Pointer to inserted node.
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

            if (m_compFunc(data, *root->m_data)) {
                return insert(&(root->m_leftNode), root, data);
            } else {
                return insert(&(root->m_rightNode), root, data);
            }
        }

        //! Private insert function.

        //! Creates new node with provided data (moves it), inserts it in correct place.
        //! @param rootPtr Pointer to local root.
        //! @param parentPtr Pointer to a parent node.
        //! @param data Data to insert in node.
        //! @return Pointer to inserted node.
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

            if (m_compFunc(data, *root->m_data)) {
                return insert(&(root->m_leftNode), root, std::move(data));
            } else {
                return insert(&(root->m_rightNode), root, std::move(data));
            }
        }

        //! Private search functon.

        //! Searches for data in subtree starting from root.
        //! @param root Local root.
        //! @param data Data we are searching for.
        //! @return Pointer to node with data if exist, nullptr otherwise.
        const m_Node *search(m_Node *root, const T &data) const {
            if (!root) return nullptr;

            if (data == *root->m_data) return root;

            if (data < *root->m_data)
                return search(root->m_leftNode, data);
            else
                return search(root->m_rightNode, data);
        }

    private:
        size_t m_numOfElements{};                            //!< Stores number of nodes in binary search tree.
        m_Node *m_rootNode{};                                //!< Pointer to a root node of a binary search tree.
        std::function<bool(const T &, const T &)> m_compFunc;//!< Comparison criteria functor
    };

}// namespace simple
#endif// BST_H
