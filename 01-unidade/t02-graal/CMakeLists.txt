cmake_minimum_required(VERSION 3.5)
project(GraalLibrary VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )

### [1] Application target
# set the include path
include_directories( include )
include_directories( tests/include/tm )

# # Add the test target
# add_executable( run_tests
#                 lib/test_manager.cpp
#                 test/main.cpp )

# # define C++11 standard
# set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)

# #=== Test target ===
set ( TEST_NAME "all_tests")
add_subdirectory(tests)

# This custom target runs the test via cmake.
add_custom_target(
    run_tests
    COMMAND ${TEST_NAME} 2> /dev/null 
    # COMMAND ${CMAKE_BINARY_DIR}/tests/tests
    DEPENDS ${TEST_LIB}
)
# The end
