cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BST VERSION 1.0)

add_executable(BST main.cpp BST.h LinkedList.h)
