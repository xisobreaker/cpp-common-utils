project(kgr_logger)

aux_source_directory(. SRC_FILES)
add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} kgr_common)
