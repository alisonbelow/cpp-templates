cmake_minimum_required(VERSION 3.12)

project(test_ex1 VERSION 0.0.1 LANGUAGES CXX)

set(TESTING_FOLDER_LOC ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTING_FOLDER_LOC}/bin/${TEST_PREFIX})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../..   
)

add_executable(${PROJECT_NAME} test_ex1.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main pthread)

# Add tests
add_test(
    NAME
    ${PROJECT_NAME}
    COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}}
)