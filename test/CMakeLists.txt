cmake_minimum_required(VERSION 3.0.0)

set(TESTS_EXCLUDE EXCLUDE_FROM_ALL)
if(BUILD_TESTS)
  set(TESTS_EXCLUDE)
endif(BUILD_TESTS)

add_subdirectory(endtoend)

add_custom_target(tests DEPENDS cocl patch_hostside ${BUILD_TEST_TARGETS})
add_custom_target(run-tests DEPENDS tests ${RUN_TEST_TARGETS})
