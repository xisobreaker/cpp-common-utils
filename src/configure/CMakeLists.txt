project(kgr_configure)

aux_source_directory(. DIR_LIB_SRCS)
add_library(${PROJECT_NAME} ${DIR_LIB_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${KGR_COMMON_INCLUDE_DIR})