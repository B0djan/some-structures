cmake_minimum_required(VERSION 3.22)
project(some_structures)

set(CMAKE_CXX_STANDARD 14)

include_directories(array)
include_directories(hash_table)
include_directories(list)
include_directories(specific)

add_executable(some_structures
    array/array.h
    hash_table/Pair.h
    hash_table/UnorderedMap.h
    list/List.h
    list/ListIterator.h
    main.cpp)
