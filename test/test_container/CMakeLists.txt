cmake_minimum_required(VERSION 3.10)

project(test_container)

aux_source_directory(. DIR_SOURCES)
add_executable(${PROJECT_NAME} ${DIR_SOURCES})

target_link_libraries(${PROJECT_NAME} kgr_common)
target_link_libraries(${PROJECT_NAME} kgr_container)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})