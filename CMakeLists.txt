cmake_minimum_required(VERSION 3.22)
project(frequency_dictionary)

set(CMAKE_CXX_STANDARD 14)

include_directories(array)
include_directories(hash_table)
include_directories(list)
include_directories(specific)

add_executable(frequency_dictionary
        list/list.h
        list/list_iterator.h
        hash_table/unordered_map.h
        specific/frequency_dictionary.h
    main.cpp)
