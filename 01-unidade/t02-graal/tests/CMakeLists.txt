# Using TestManager Library
# Compile the TestManagere first into a lib.
set( TEST_LIB "TM")
add_library(${TEST_LIB} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tm/test_manager.cpp)
target_include_directories( ${TEST_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties( ${TEST_LIB} PROPERTIES CXX_STANDARD 17 )

# Add the always present main test...
add_executable( ${TEST_NAME} main.cpp )
target_include_directories( ${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#... and any other test source that have been created.
# target_sources( ${TEST_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_01.cpp" )
# We link the test application with the TM library.
target_link_libraries( ${TEST_NAME} PRIVATE ${TEST_LIB} )
