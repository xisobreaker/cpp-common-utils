project(xiso_network)

aux_source_directory(. DIR_LIB_SRCS)
add_library (${PROJECT_NAME} ${DIR_LIB_SRCS})

target_link_libraries(${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${XISO_COMMON_INCLUDE_DIR})