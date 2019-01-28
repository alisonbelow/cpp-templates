cmake_minimum_required(VERSION 3.12)

include(${PROJECT_SOURCE_DIR}/cmake/googletest-download-macro.cmake)

# Call macro from googletest-macro.cmake
# PARAMS: download module path, download root path
download_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/googletest
)

set(TEST_PREFIX compiling_and_linking )
add_subdirectory(ex1_inclusion)
add_subdirectory(ex2_expl_instantiation)
add_subdirectory(ex3_inclusion_with_expl_instantiation)