cmake_minimum_required(VERSION 3.12)

project(test_ex3 VERSION 0.0.1 LANGUAGES CXX)

set(TESTING_FOLDER_LOC ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/bin/${TEST_PREFIX})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../..   
)

add_executable(${PROJECT_NAME} test_ex3.cpp)

set(EX3_STATIC_LIB ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libex3_incl_w_expl_instantiation.a)

target_link_libraries(${PROJECT_NAME} ${EX3_STATIC_LIB} gtest_main pthread)

# Add tests
add_test(
    NAME
    ${PROJECT_NAME}
    COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}}
)