project(xiso_container)

aux_source_directory(. SRC_FILES)
add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} xiso_common)
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${XISO_COMMON_INCLUDE_DIR})