#include <iostream>
#include <fstream>

#include "BST.h"

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

    Vector3(Vector3 &&other)  noexcept : x(other.x), y(other.y), z(other.z) {
        ar = other.ar;
        other.ar = nullptr;
    }

    ~Vector3() { delete[] ar; }

    Vector3 &operator=(const Vector3 &other) {
        if(this != &other) {
            std::cout << "Copy\n";
            x = other.x;
            y = other.y;
            z = other.z;
            ar = new int[5];
            for (int i = 0; i < 5; i++) ar[i] = other.ar[i];
        }
        return *this;
    }

    Vector3 &operator=(Vector3 &&other)  noexcept {
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
        os << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
        return os;
    }

    bool operator<(const Vector3 &other) const { return x < other.x; }
    bool operator<=(const Vector3 &other) const { return x <= other.x; }
    bool operator==(const Vector3 &other) const { return x == other.x; }
};

template<typename T>
void printTree(simple::BinarySearchTree<T> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto & e:tree)
        std::cout << e << " ";

    std::cout << "\n-------------------------------------" << std::endl;
}

template<>
void printTree(simple::BinarySearchTree<Vector3> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for  (auto & e:tree)
        std::cout << e << "\n";

    std::cout << "-------------------------------------" << std::endl;
}

template<>
void printTree(simple::BinarySearchTree<std::pair<int *, std::string>> &tree) {
    std::cout << "number of elements: " << tree.size() << "\n";
    for (auto & e:tree)
        std::cout << *e.first << ", " << e.second << " \n";

    std::cout << "-------------------------------------" << std::endl;
}

int main() {
    simple::BinarySearchTree<int> iBST;

    iBST.insert(10);
    iBST.insert(7);
    iBST.insert(15);
    iBST.insert(17);
    iBST.insert(5);
    iBST.insert(226);
    iBST.insert(12);
    iBST.insert(20);
    iBST.insert(13);
    auto it = iBST.begin();
    simple::BinarySearchTreeIterator<int> it7;

    std::cout << *it << " " << *++it << " " << *++it <<  std::endl;

    std::cout << iBST.root() << std::endl;
    std::cout << *iBST.search(7) << std::endl;
    printTree(iBST);
    std::cout << *it << " next -> " << *(++it) << ", next using it++ "
              << "*it: " << *it << ", and it++: " << *(it++)
              << ", and it after " << *it << ", it+2:" << *(it + 2)
              << std::endl;
    // std::cout << *iBST.search(123) << std::endl;
    iBST.remove(20);
    iBST.remove(10);
    iBST.remove(123);
    printTree(iBST);
    iBST.search(123);
    std::cout << std::endl;
    std::cout << iBST.root() << std::endl;

    iBST.remove(5);
    printTree(iBST);
    std::cout << std::endl;
    iBST.remove(226);
    printTree(iBST);
    std::cout << std::endl;
    iBST.remove(17);
    printTree(iBST);

    simple::BinarySearchTree<std::string> sBST;

    sBST.insert("root");
    sBST.insert("sdf");
    sBST.insert("awer");
    sBST.insert("asdxcv");
    sBST.insert("ergv");

    std::cout << sBST.root() << std::endl;
    std::cout << *sBST.search("sdf") << std::endl;
    std::cout << sBST.min() << " " << iBST.min() << " " << iBST.max()
              << std::endl;
    printTree(sBST);
    std::cout << std::endl;
    auto it2 = sBST.begin();
    std::cout << *it2 << std::endl;
    std::cout << "++it2: " << *++it2 << ", ++it2: " << *++it2
              << ", it2+2: " << *(it2 + 2) << std::endl;

    simple::BinarySearchTree<Vector3> treeOfVec3;
    Vector3 yes(1);
    yes.ar[0] = 1;
    treeOfVec3.insert(std::move(yes));
    treeOfVec3.insert({2.4f, 1.6f, 0.9f});
    treeOfVec3.insert(Vector3(1.6f));
    printTree(treeOfVec3);

    printTree(sBST);
    printTree(iBST);
//    auto copy = sBST;
    auto moved = std::move(iBST);


    printTree(treeOfVec3);

    printTree(moved);

    moved.clear();
    moved.insert(85);
    moved.insert(45);
    moved.insert(195);

    printTree(moved);

    sBST.clear();
    printTree(sBST);
    sBST.insert("Very nice");
    printTree(sBST);

    simple::BinarySearchTree<std::pair<int*, std::string>> test;
    int a {3}, b{7};
    test.insert(std::pair(&a, "sedsf"));
    test.emplace(&b, "asdwaqeq");
    printTree(test);

    simple::BinarySearchTree<int> asd{12, 43, 65, 73, 10, 23, 6, -1};
    simple::BinarySearchTree<int> ewq = {65, 73, 123, 54, 10, 23, 6, -1};

    simple::BinarySearchTree<std::pair<int*, std::string>> test2{{&b, "nbmjkh"}, {&a, "zxcvnbydf"}};
    printTree(test2);
    printTree(asd);
    printTree(ewq);

    std::ofstream oFile("out.txt");
    oFile << ewq;
    oFile.close();

    std::ifstream inFile("out.txt");
    simple::BinarySearchTree<int> final;
    inFile >> final;
    inFile.close();

    printTree(final);

    auto bs = sBST;

    printTree(bs);

    simple::BinarySearchTree<Vector3> round2(treeOfVec3);

    printTree(round2);
}
