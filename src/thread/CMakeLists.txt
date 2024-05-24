project(kgr_thread)

aux_source_directory(. DIR_LIB_SRCS)
add_library (${PROJECT_NAME} ${DIR_LIB_SRCS})

target_link_libraries(${PROJECT_NAME} pthread)
