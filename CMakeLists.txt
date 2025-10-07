cmake_minimum_required(VERSION 3.16)
project(KronosDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71.0 REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Threads REQUIRED)

add_executable(
        KronosDB
        src/main.cpp
        src/KeyValueStore.h
        src/KeyValueStore.cpp
        src/Server.cpp
        src/Server.h
        src/Session.h
        src/Session.cpp
        src/Persistence.h
        src/Persistence.cpp
)

add_executable(
        kronos-cli
        src/cli.cpp
)

# Link all required libraries to the executable
target_link_libraries(KronosDB PRIVATE
        Boost::system
        Boost::thread
        Threads::Threads
)

target_link_libraries(kronos-cli PRIVATE
        Boost::system
        Boost::thread
        Threads::Threads
)

# Add Windows-specific libraries only when compiling on Windows
if(WIN32)
    target_link_libraries(KronosDB PRIVATE ws2_32 mswsock)
    target_link_libraries(kronos-cli PRIVATE ws2_32 mswsock)
endif()