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

# 收集所有头文件（可选，用于 IDE 显示）
file(GLOB HEADER_FILES
    include/*.h
    include/*.hpp
)

# 所有实现文件
file(GLOB SRC_FILES
    src/*.cpp
)

# 所有测试文件
file(GLOB TEST_FILES
    test/test_*.cpp
    test/test_*_*.cpp
    test/test.cpp
)

# 为每个 test_xxx.cpp 生成一个可执行文件
foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    # 如果有实现文件就添加，没有也不影响编译
    if(SRC_FILES)
        add_executable(${test_name}
            ${test_file}
            ${SRC_FILES}
            ${HEADER_FILES}  # 添加头文件以便在 IDE 中显示
        )
    else()
        add_executable(${test_name}
            ${test_file}
            ${HEADER_FILES}
        )
    endif()
endforeach()
