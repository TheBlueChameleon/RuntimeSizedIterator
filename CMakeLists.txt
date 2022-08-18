cmake_minimum_required(VERSION 3.5)

project(RuntimeSizedIterator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RuntimeSizedIterator
    main.cpp
    runtimesizediterator.h runtimesizediterator.cpp
)
