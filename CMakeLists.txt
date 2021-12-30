cmake_minimum_required(VERSION 3.20)
project(anothersql)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g -pthread")
add_executable(server main.cpp src/_macro.cpp src/Database.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/memory)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/sync)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/io)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/recovery)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/concurrency)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/parallelism)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/index)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/storage)


target_link_libraries(server memory)