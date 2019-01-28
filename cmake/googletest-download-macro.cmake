# Adapted from https://www.testcookbook.com/book/cpp/setting-up-cmake-google-test.html
#              https://github.com/bast/gtest-demo/blob/master/cmake/googletest.cmake
#              https://github.com/google/googletest/blob/master/googletest/README.md

macro(download_googletest _download_module_path _download_root)
    set(GOOGLETEST_DOWNLOAD_ROOT ${_download_root})
    configure_file(
        ${_download_module_path}/CMakeLists.txt.in
        ${_download_root}/CMakeLists.txt
        @ONLY
    )
    unset(GOOGLETEST_DOWNLOAD_ROOT)

    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${_download_root}
    )

    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY ${_download_root}
    )

    # adds the targets: gtest, gtest_main, gmock, gmock_main
    add_subdirectory(
        ${_download_root}/googletest-src
        ${_download_root}/googletest-build
    )

endmacro()