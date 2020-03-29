cmake_minimum_required(VERSION 3.0)
project(c_projects_word_finder)
set(CMAKE_CXX_FLAGS "-std=c++11 -coverage")
set(CMAKE_C_FLAGS "-coverage")

# Download and unpack googletest at configure time
configure_file(tests/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE Debug)
file(GLOB sources "source/*.c")
add_library(${PROJECT_NAME}_dlib SHARED ${sources})
target_compile_options(${PROJECT_NAME}_dlib PRIVATE -Wall -Wextra -pedantic -Werror -pthread)
add_executable(${PROJECT_NAME}_test tests/test.c)
target_compile_options(${PROJECT_NAME}_test PRIVATE -Wall -Wextra -pedantic -Werror -pthread)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME}_dlib pthread)