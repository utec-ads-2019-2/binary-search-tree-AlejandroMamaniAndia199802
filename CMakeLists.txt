cmake_minimum_required(VERSION 3.13.4)
project(binary-search-tree-AlejandroMamaniAndia199802)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)



add_executable(binary-search-tree-AlejandroMamaniAndia199802 iterator.h bstree.h main.cpp node.h tester/tester.h tester/tester.cpp mocker/mocker.h mocker/mocker.cpp)