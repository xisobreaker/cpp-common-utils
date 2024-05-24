cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Chosse the type of build, Debug or Release" FORCE)
endif()

project(cpp_common_utils VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

set(project_include_dirs
    "${CMAKE_SOURCE_DIR}/include/common"
    "${CMAKE_SOURCE_DIR}/include/configure"
    "${CMAKE_SOURCE_DIR}/include/container"
    "${CMAKE_SOURCE_DIR}/include/crypto"
    "${CMAKE_SOURCE_DIR}/include/logger"
    "${CMAKE_SOURCE_DIR}/include/thread")

include_directories(${project_include_dirs})

# 添加子目录
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()