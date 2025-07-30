cmake_minimum_required(VERSION 3.31)
project(Multithreaded_DB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        Multithreaded_DB
        src/main.cpp
#        src/KeyValueStore.h
#        src/KeyValueStore.cpp
)

find_package(Threads REQUIRED)

#Linking threads library to executable
target_link_libraries(Multithreaded_DB PRIVATE Threads::Threads)