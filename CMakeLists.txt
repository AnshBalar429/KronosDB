cmake_minimum_required(VERSION 3.16)
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
        src/Persistence.h
        src/Persistence.cpp
)

# Link all required libraries to the executable
target_link_libraries(Multithreaded_DB PRIVATE
        Boost::system
        Boost::thread
        Threads::Threads
)

# Add Windows-specific libraries only when compiling on Windows
if(WIN32)
    # Corrected the executable name here to match
    target_link_libraries(Multithreaded_DB PRIVATE ws2_32 mswsock)
endif()