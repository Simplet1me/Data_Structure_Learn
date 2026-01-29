cmake_minimum_required(VERSION 3.20)
project(DataStructure)

# 使用 MSVC 时的一些友好设置
if (MSVC)
    add_compile_options(/W4)
    add_compile_options(/utf-8)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 所有实现文件
file(GLOB SRC_FILES
    src/*.cpp
)

# 所有测试文件
file(GLOB TEST_FILES
    test/test_*.cpp
    test/test.cpp
    test/test_sort.cpp
    test/test_queue.cpp
)

# 为每个 test_xxx.cpp 生成一个可执行文件
foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}
        ${test_file}
        ${SRC_FILES}
    )
endforeach()
