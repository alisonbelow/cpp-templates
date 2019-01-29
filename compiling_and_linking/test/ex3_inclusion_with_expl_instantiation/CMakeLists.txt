cmake_minimum_required(VERSION 3.12)

project(test_ex3 VERSION 0.0.1 LANGUAGES CXX)

set(TESTING_FOLDER_LOC ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/bin/${TEST_PREFIX})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../..   
)

add_executable(${PROJECT_NAME}a test_ex3a.cpp)
add_executable(${PROJECT_NAME}b test_ex3b.cpp)

set(EX3_STATIC_LIB ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libex3_incl_w_expl_instantiation.a)

target_link_libraries(${PROJECT_NAME}a ${EX3_STATIC_LIB} gtest_main pthread)
target_link_libraries(${PROJECT_NAME}b gtest_main pthread)

# Add tests
add_test(
    NAME
    ${PROJECT_NAME}a
    COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}a}
)

add_test(
    NAME
    ${PROJECT_NAME}b
    COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}b}
)