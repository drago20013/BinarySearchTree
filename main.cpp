#include <iostream>

#include "BST.h"

struct Vector3 {
    float x{}, y{}, z{};
    int *ar;

    Vector3() { ar = new int[5]; }

    Vector3(float scalar) : x(scalar), y(scalar), z(scalar) { ar = new int[5]; }

    Vector3(float x, float y, float z) : x(x), y(y), z(z) { ar = new int[5]; }

    Vector3(const Vector3 &other) {
        std::cout << "Copy\n";
        x = other.x;
        y = other.y;
        z = other.z;
        ar = new int[5];
        for (int i = 0; i < 5; i++) ar[i] = other.ar[i];
    }

    Vector3(Vector3 &&other) : x(other.x), y(other.y), z(other.z) {
        std::cout << "Move\n";
        ar = other.ar;
        other.ar = nullptr;
    }

    ~Vector3() { delete[] ar; }

    Vector3 &operator=(const Vector3 &other) {
        std::cout << "Copy\n";
        x = other.x;
        y = other.y;
        z = other.z;
        ar = new int[5];
        for (int i = 0; i < 5; i++) ar[i] = other.ar[i];
        return *this;
    }

    Vector3 &operator=(Vector3 &&other) {
        std::cout << "Move\n";
        x = other.x;
        y = other.y;
        z = other.z;
        ar = other.ar;
        other.ar = nullptr;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec) {
        os << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
        return os;
    }

    bool operator<(const Vector3 &other) const { return x < other.x; }
    bool operator==(const Vector3 &other) const { return x == other.x; }
};

int main() {
    simple::BinarySearchTree<int> iBST;

    iBST.insert(10);
    auto it = iBST.insert(7);
    iBST.insert(15);
    iBST.insert(17);
    iBST.insert(5);
    iBST.insert(226);
    iBST.insert(12);
    iBST.insert(20);
    iBST.insert(13);
    // auto it = iBST.begin();
    std::cout << *iBST.getRoot() << std::endl;
    std::cout << *iBST.search(7) << std::endl;
    iBST.inorder();
    std::cout << iBST[1] << std::endl;
    std::cout << *it << " next -> " << *(++it) << ", next using it++ "
              << "*it: " << *it << ", and it++: " << *(it++)
              << ", and it after " << *it << ", it+2:" << *(it + 2)
              << std::endl;
    // std::cout << *iBST.search(123) << std::endl;
    iBST.remove(20);
    iBST.remove(10);
    iBST.remove(123);
    iBST.inorder();
    iBST.search(123);
    std::cout << std::endl;
    std::cout << *iBST.getRoot() << std::endl;

    iBST.remove(5);
    iBST.inorder();
    std::cout << std::endl;
    iBST.remove(226);
    iBST.inorder();
    std::cout << std::endl;
    iBST.remove(17);
    iBST.inorder();
    std::cout << std::endl;

    simple::BinarySearchTree<std::string> sBST;

    sBST.insert("root");
    sBST.insert("sdf");
    sBST.insert("awer");
    sBST.insert("asdxcv");
    sBST.insert("ergv");

    std::cout << *sBST.getRoot() << std::endl;
    std::cout << *sBST.search("sdf") << std::endl;
    std::cout << *sBST.min() << " " << *iBST.min() << " " << *iBST.max()
              << std::endl;
    sBST.inorder();
    std::cout << std::endl;
    auto it2 = sBST.begin();
    std::cout << sBST[3] << std::endl;
    std::cout << *it2 << std::endl;
    std::cout << "++it2: " << *++it2 << ", ++it2: " << *++it2
              << ", it2+2: " << *(it2 + 2) << std::endl;

    //=================
    // TODO Serialization
    //

    simple::BinarySearchTree<Vector3> treeOfVec3;
    Vector3 yes(1);
    yes.ar[0] = 1;
    treeOfVec3.insert(std::move(yes));
    treeOfVec3.insert({2.4f, 1.6f, 0.9f});
    treeOfVec3.insert(Vector3(1.6f));
    treeOfVec3.inorder();
    std::cout << std::endl;
}
