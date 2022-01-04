# BinarySearchTree
###### University project, implementation of Binary Search Tree data structure. Without usage of STL containers.
![CPP](https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B)
![Linux](https://img.shields.io/badge/os-linux-brightgreen)
![Mac](https://img.shields.io/badge/os-mac-brightgreen)
![Windows](https://img.shields.io/badge/os-windows-brightgreen)

### API
* Default constructor
* Copy/Move constructors
* Initializer list constructor
* Copy/Move operators
* Serialize/Deserialize function (only for types without pointers)
* Insert
* Emplace
* Remove
* Search
* Clear
* Root
* Size
* Min
* Max
* Save/Read to/from file using << / >> operator
* Insert element using << operator
* Forward Iterator (inorder)
* Reverse Iterator (inorder)

First inserted element is the root.

## Usage
* Clone repository or download [BST.h](BST.h) and [LinkedList.h](LinkedList.h)
* Include it to your project
```cpp
#include <iostream>
#include "BST.h"

int main(){
    simple::BinarySearchTree<int> iTree{12, 35, 20, 68};
    simple::BinarySearchTree<char> cTres{'b', 's', 't'};

    for(const auto &e:iTree){
        std::cout << e << "\n";
    }
}
```

## Dependencies
```
LinkedList.h
```
