cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION 1)
if($ENV{TRAVIS_BUILD_NUMBER})
    set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(matrix VERSION 0.0.${PATCH_VERSION})

find_package(GTest REQUIRED)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/tests")

add_executable(matrix ${SOURCE_PATH}/main.cpp
                      ${SOURCE_PATH}/matrix.cpp
)
add_executable(test_matrix  ${TEST_PATH}/gtest.cpp)

find_package(Threads)
target_link_libraries(test_matrix ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(
    matrix
    test_matrix
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

set_target_properties(
    test_matrix
    PROPERTIES
        INCLUDE_DIRECTORIES ${SOURCE_PATH}
)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(test_matrix PRIVATE
       /W4
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
   target_compile_options(test_matrix PRIVATE
       -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT zonner2785@gmail.com)

include(CPack)

enable_testing()

add_test(NAME test_matrix COMMAND test_matrix)
