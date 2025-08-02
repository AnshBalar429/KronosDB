cmake_minimum_required(VERSION 3.31)
project(Multithreaded_DB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71.0 REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Threads REQUIRED)

add_executable(
        Multithreaded_DB
        src/main.cpp
        src/KeyValueStore.h
        src/KeyValueStore.cpp
        src/Server.cpp
        src/Server.h
        src/Session.h
        src/Session.cpp
)

#Linking threads library to executable
target_link_libraries(Multithreaded_DB PRIVATE Threads::Threads ${Boost_LIBRARIES} ws2_32
)