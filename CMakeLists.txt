cmake_minimum_required(VERSION 3.10)
project(TypeAhead)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES WordTree.hpp rlutil.h)
set(SOURCE_FILES WordTree.cpp)
set(UNIT_TEST_FILES TestWordTree.cpp)

add_executable(TypeAhead ${SOURCE_FILES} main.cpp)

if (MSVC)
    target_compile_options(TypeAhead PRIVATE /W4 /permissive-)
else()
    target_compile_options(TypeAhead PRIVATE -Wall -Wextra -pedantic )
endif()

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(UnitTestRunner ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES})
target_link_libraries(UnitTestRunner gtest gtest_main)

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()
    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS})

    add_dependencies(TypeAhead ClangFormat)
    add_dependencies(UnitTestRunner ClangFormat)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt dictionary.txt
)