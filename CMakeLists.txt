cmake_minimum_required(VERSION 3.10)

project(cpp_common_utils VERSION 0.0.1)

# 指定使用 C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Chosse the type of build, Debug or Release" FORCE)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL x86_64)
    set(SYSTEM_PROCESSOR x86_64)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL aarch64)
    set(SYSTEM_PROCESSOR aarch64)
endif()

# 设置输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# 生成文件
configure_file(
    "${CMAKE_SOURCE_DIR}/config.h.in"
    "${CMAKE_SOURCE_DIR}/include/common/config/config.h")

set(XISO_COMMON_INCLUDE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/include/common"
    "${CMAKE_CURRENT_LIST_DIR}/include/configure"
    "${CMAKE_CURRENT_LIST_DIR}/include/container"
    "${CMAKE_CURRENT_LIST_DIR}/include/crypto"
    "${CMAKE_CURRENT_LIST_DIR}/include/filesystem"
    "${CMAKE_CURRENT_LIST_DIR}/include/logger"
    "${CMAKE_CURRENT_LIST_DIR}/include/thread")

include_directories(${XISO_COMMON_INCLUDE_DIR})

# 添加子目录
add_subdirectory(src)
add_subdirectory(examples)

include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()