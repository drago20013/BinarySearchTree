/**
 * @file main.cpp
 * @author Michal Smaluch (https://github.com/drago20013)
 * @brief Main file with testing of binary search tree data structure.
 * @version 1.2
 * @date 2022-01-05
 *
 * @copyright GNU Public License v3.0
 */

#include <functional>
#include <iomanip>
#include <iostream>

#include "BST.h"

typedef std::pair<int *, std::string> myPair;

//! Helper struct used for testing
struct Vector3 {
    float x{}, y{}, z{};
    int *ar;

    Vector3() { ar = new int[5]; }

    explicit Vector3(float scalar) : x(scalar), y(scalar), z(scalar) { ar = new int[5]; }

    Vector3(float x, float y, float z) : x(x), y(y), z(z) { ar = new int[5]; }

    Vector3(const Vector3 &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        ar = new int[5];
        for (int i = 0; i < 5; i++) ar[i] = other.ar[i];
    }

    Vector3(Vector3 &&other) noexcept : x(other.x), y(other.y), z(other.z) {
        ar = other.ar;
        other.ar = nullptr;
    }

    ~Vector3() { delete[] ar; }

    Vector3 &operator=(const Vector3 &other) {
        if (this != &other) {
            std::cout << "Copy\n";
            x = other.x;
            y = other.y;
            z = other.z;
            ar = new int[5];
            for (int i = 0; i < 5; i++) ar[i] = other.ar[i];
        }
        return *this;
    }

    Vector3 &operator=(Vector3 &&other) noexcept {
        if (this != &other) {
            std::cout << "Move\n";
            x = other.x;
            y = other.y;
            z = other.z;
            ar = other.ar;
            other.ar = nullptr;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec) {
        os << std::left << "x: " << std::setw(5) << vec.x << "\ty: " << std::setw(5) << vec.y << "\tz: " << std::setw(5) << vec.z;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Vector3 &vec) {
        std::string tmp;
        is >> tmp >> vec.x >> tmp >> vec.y >> tmp >> vec.z;
        return is;
    }

    bool operator<(const Vector3 &other) const { return x < other.x; }
    bool operator<=(const Vector3 &other) const { return x <= other.x; }
    bool operator==(const Vector3 &other) const { return x == other.x; }
};

//! Template function used for printing tree.
//! It uses forward iterator and print data in order.
template<typename T>
void printTree(simple::BinarySearchTree<T> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto &e: tree)
        std::cout << e << " ";

    std::cout << "\n-------------------------------------" << std::endl;
}

//! Template function used for printing tree.
//! It uses reverse iterator and print data in reverse order.
template<typename T>
void reversePrint(simple::BinarySearchTree<T> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto rIt = tree.rbegin(); rIt != tree.rend(); rIt++)
        std::cout << *rIt << " ";

    std::cout << "\n-------------------------------------" << std::endl;
}

//! Specialized template for Vector3.
template<>
void printTree(simple::BinarySearchTree<Vector3> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto &e: tree)
        std::cout << e << "\n";

    std::cout << "-------------------------------------" << std::endl;
}

//! Specialized template for Vector3.
//! It uses reverse iterator and print data in reverse order.
template<>
void reversePrint(simple::BinarySearchTree<Vector3> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto rIt = tree.rbegin(); rIt != tree.rend(); rIt++)
        std::cout << *rIt << "\n";

    std::cout << "-------------------------------------" << std::endl;
}

//! Specialized template for std::pair<int*, std::string>
template<>
void printTree(simple::BinarySearchTree<myPair> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto &[x, y]: tree)
        std::cout << *x << " " << y << " \n";

    std::cout << "-------------------------------------" << std::endl;
}

//! Specialized template for std::pair<int*, std::string>
//! It uses reverse iterator and print data in reverse order.
template<>
void reversePrint(simple::BinarySearchTree<myPair> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto rIt = tree.rbegin(); rIt != tree.rend(); rIt++)
        std::cout << *rIt->first << " " << rIt->second << " \n";

    std::cout << "-------------------------------------" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const myPair &src) {
    os << *src.first << " " << src.second;
    return os;
}

std::istream &operator>>(std::istream &is, myPair &src) {
    is >> *src.first >> src.second;
    return is;
}

//! Helper function, creates 3 trees of T type and test them.
template<typename T>
void testTree(
        std::initializer_list<T> init,
        int nrOfTest = 0,
        const T &searchFor = {},
        const T &toRemove_1 = {},
        const T &toRemove_2 = {},
        const T &toRemove_3 = {},
        std::function<bool(const T &a, const T &b)> compFunc = [](const T &a, const T &b) { return a < b; }) {

    simple::BinarySearchTree<T> testTree1(compFunc);
    simple::BinarySearchTree<T> testTree2(compFunc);
    simple::BinarySearchTree<T> testTree3(init, compFunc);

    //emplace
    for (auto &e: init) testTree2.emplace(e);

    //copy operator
    testTree1 = testTree2;

    std::cout << "root of testTree1: " << testTree1.root() << std::endl;
    if (testTree1.search(searchFor)) std::cout << "Found " << searchFor << " in testTree1" << std::endl;

    //removing from testTrees2
    testTree2.remove(toRemove_1);
    testTree2.remove(toRemove_2);
    testTree2.remove(toRemove_3);

    //printing trees
    std::cout << "testTree1\t";
    printTree(testTree1);
    std::cout << "testTree2\t";
    printTree(testTree2);
    std::cout << "testTree3\t";
    printTree(testTree3);

    //printing testTree using reverse iterator
    std::cout << "reversed testTree1\t";
    reversePrint(testTree1);
    std::cout << "reversed testTree2\t";
    reversePrint(testTree2);
    std::cout << "reversed testTree3\t";
    reversePrint(testTree3);

    //saving testTree3 to a text file, clearing it and then reading from text file
    if (nrOfTest != 0) {
        std::string sFileName{"out" + std::to_string(nrOfTest) + ".txt"};
        std::ofstream oFile(sFileName);
        oFile << testTree3;
        oFile.close();

        testTree3.clear();

        std::ifstream inFile(sFileName);
        inFile >> testTree3;
        inFile.close();

        std::cout << "testTree3 after saving, clearing and reading from file: " << std::endl;
        printTree(testTree3);
    }
}

int main() {
    int nrOfTest{1};
    // Testing BST with ints
    testTree<int>({4, 5, 7, 3, 1, 50, 7, 5, 9, 10, 17, 226, 20}, nrOfTest++,
                  226, 7, 5, 9,
                  [](const int &a, const int &b) { return a > b; });

    // Testing BST with doubles
    testTree({4.32, 5.54, 7.76, 3.876, 1.234, 50.23478, 7.897, 5.2345, 9.789, 10.234, 17.23451, 226.123, 20.876}, nrOfTest++);

    // Testing BST with Vector3s
    testTree<Vector3>({Vector3(),
                       Vector3(3),
                       Vector3(45.2f, 32.1f, 87.9f)},
                      nrOfTest++,
                      Vector3(45.2f, 32.1f, 87.9f),
                      Vector3(),
                      Vector3(45.2f, 32.1f, 87.9f),
                      Vector3(),
                      [](const Vector3 &a, const Vector3 &b) { return a.y > b.y; });

    // Testing BST with std::strings
    testTree<std::string>({"abc", "def", "ghi"}, 0, "def", "ghi", "abc");

    //Testing BST with std::pair<int *, std::string>
    int a{10}, b{69}, c{420};

    testTree<myPair>({myPair(&a, "another"), myPair(&b, "one"), myPair(&c, "bite the dust")}, 0,
                     myPair(&a, "another"),
                     myPair(&c, "bite the dust"));

    // reading data in text format from file
    simple::BinarySearchTree<int> iTree;
    std::ifstream inFile("in.txt");
    if (inFile) {
        inFile >> iTree;
        inFile.close();
    }

    // Reading data in text format from file, saving it in binary and then reading in binary
    iTree.serialize("data.bin");

    //changing comparison criteria
    simple::BinarySearchTree<int> iTree2([](const int &a, const int &b) { return a > b; });

    simple::BinarySearchTree<Vector3> asd;

    iTree2.deserialize("data.bin");
    printTree(iTree);
    printTree(iTree2);
    std::cout << "root of iTree: " << iTree.root() << ", root of iTree2: " << iTree2.root() << std::endl;
}
