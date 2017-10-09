cmake_minimum_required(VERSION 3.0.0)

option(BUILD_TESTS OFF)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        SET(CMAKE_INSTALL_PREFIX
            "$ENV{HOME}/coriander" CACHE PATH "Installation prefix, default '${HOME}/coriander'" FORCE
        )
    else()
        SET(CMAKE_INSTALL_PREFIX
            "$ENV{HOME}/coriander" CACHE PATH "Installation prefix, default '${HOME}/coriander'" FORCE
        )
    endif()
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

SET(CORIANDER_DIR ${CMAKE_INSTALL_PREFIX})

SET(COCL_CMAKE "$ENV{COCL_CMAKE}" CACHE PATH "Cocl CMake includes (leave empty to replace with generated default)")
if(NOT COCL_CMAKE)
    set(COCL_CMAKE "${CORIANDER_DIR}/share/cocl")
endif()

# bring in just the targets we need/depend on
# (if we bring in all targets, the solver target has the same name as ourselves, and conflicts)
include(${COCL_CMAKE}/cocl_vars.cmake)
include(${COCL_CMAKE}/cocl_impl.cmake)
include(${COCL_LIB}/cocl/cocl-targets.cmake)
include(${COCL_LIB}/coriander_plugins/corianderclblast-targets.cmake)


SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/coriander_plugins")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_MACOSX_RPATH TRUE)

if(WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc ${PLATFORM_OPTIONS}")
else()
    set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -g ${PLATFORM_OPTIONS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
endif()
add_definitions(-DUSE_CLEW)

add_library(coriandersolver SHARED src/cocl_solver_dn.cpp)
target_include_directories(coriandersolver PRIVATE "${CORIANDER_DIR}/include")
target_include_directories(coriandersolver PRIVATE "include")
target_include_directories(coriandersolver SYSTEM BEFORE PRIVATE "${CORIANDER_DIR}/include/clew/proxy-headers")
target_include_directories(coriandersolver SYSTEM BEFORE PRIVATE "${CORIANDER_DIR}/include/coriander_plugins/corianderclblast")

target_include_directories(coriandersolver PRIVATE ${CLANG_HOME}/include)
target_link_libraries(coriandersolver cocl)

if(BUILD_TESTS)
    # for testing
    set(coriandersolver_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(GTEST_HOME ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest)
    add_subdirectory(test)
endif()

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/coriandersolver.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/coriandersolver.cmake" @ONLY)
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/cmake/coriandersolver.cmake DESTINATION share/cocl/coriander_plugins)

INSTALL(FILES include/cusolverDn.h DESTINATION ${CORIANDER_DIR}/include/coriander_plugins/coriandersolver)
FILE(GLOB SOLVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/coriander-solver/*.h)
INSTALL(FILES ${SOLVER_HEADERS} DESTINATION ${CORIANDER_DIR}/include/coriander_plugins/coriandersolver/coriander-solver)

install(TARGETS coriandersolver EXPORT coriandersolver-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/coriander_plugins
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/coriander_plugins
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/coriander_plugins
)
install(EXPORT coriandersolver-targets DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/coriander_plugins)
