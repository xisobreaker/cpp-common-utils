project(xiso_common)

aux_source_directory(. DIR_SOURCES)
add_library(${PROJECT_NAME} ${DIR_SOURCES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${XISO_COMMON_INCLUDE_DIR})