cmake_minimum_required(VERSION 3.5)
project(VTRAY CXX)

# require a C++11 compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Gui REQUIRED)

# EDIT: add your (non-test) source files to this list
set(src
  
  )

# EDIT: add any additional test source files to this list
set(test_src unittests.cpp)

# You should not need to edit below this line
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# create unittests
add_executable(unittests catch.hpp ${test_src} ${src})
target_link_libraries(unittests Qt5::Gui)

# create the vtray executable
add_executable(vtray vtray.cpp ${src})
target_link_libraries(vtray Qt5::Gui)

enable_testing()

# unit tests
add_test(unit unittests)

# integration tests
add_test(test0 vtray ${CMAKE_SOURCE_DIR}/tests/scene0.json output0.png)
add_test(test1 vtray ${CMAKE_SOURCE_DIR}/tests/scene1.json output1.png)
add_test(test2 vtray ${CMAKE_SOURCE_DIR}/tests/scene2.json output2.png)
add_test(test3 vtray ${CMAKE_SOURCE_DIR}/tests/scene3.json output3.png)
add_test(test4 vtray ${CMAKE_SOURCE_DIR}/tests/scene4.json output4.png)

set_tests_properties(test3 PROPERTIES WILL_FAIL ON)
set_tests_properties(test4 PROPERTIES WILL_FAIL ON)

# look for perceptualdiff
find_program(PDIFF perceptualdiff)
if(PDIFF)
  add_test(test0diff perceptualdiff --sum-errors --output output0diff.png
    ${CMAKE_SOURCE_DIR}/tests/scene0.png output0.png )
  add_test(test1diff perceptualdiff --threshold 200000 --sum-errors --output output1diff.png
    ${CMAKE_SOURCE_DIR}/tests/scene1.png output1.png )
  add_test(test2diff perceptualdiff --threshold 400000 --sum-errors --output output2diff.png
    ${CMAKE_SOURCE_DIR}/tests/scene2.png output2.png)
endif()

# On Linux, using GCC, to enable coverage on tests -DCOVERAGE=TRUE
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND COVERAGE)
  message("Enabling Test Coverage")
  SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set_target_properties(unittests PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS} )
  target_link_libraries(unittests gcov)
  add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/coverage.sh)
endif()

# On Linux, using GCC, to enable coverage on tests -DMEMORY=TRUE
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND MEMORY)
  add_custom_target(memtest
    COMMAND valgrind ${CMAKE_BINARY_DIR}/unittests)
endif()

# enable clang-tidy with -DTIDY=TRUE
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND TIDY)
  add_custom_target(tidy
    COMMAND ${CMAKE_COMMAND} -E env "source=${CMAKE_CURRENT_SOURCE_DIR}" env "build=${CMAKE_CURRENT_BINARY_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/tidy.sh
    )
endif()
