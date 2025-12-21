cmake_minimum_required(VERSION 3.28)
project(Bookstore_2025)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(code
        include/Memory.h
        src/main.cpp
        include/User.h
        include/Account.h
        include/DataMap.h
        src/Account.cpp
        include/Book.h
        include/Repository.h
        src/Repository.cpp
        src/Account.cpp
        include/OperationLog.h
        src/Book.cpp
        src/OperationLog.cpp
        前置作业/增加pre_node的块链.cpp
        前置作业/旧版的DataMap存档.cpp)
