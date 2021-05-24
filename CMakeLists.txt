cmake_minimum_required(VERSION 3.11)

project(CMakeTemplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Force colored error output from the compiler when using Ninja
if(
  CMAKE_GENERATOR STREQUAL "Ninja" AND
  ((CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_C_COMPILER_VERSION VERSION_LESS 4.9) OR
  (CMAKE_C_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_C_COMPILER_VERSION VERSION_LESS 3.5))
)
  # Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
  # Rationale in https://github.com/ninja-build/ninja/issues/814
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()


add_library(coverage_config INTERFACE)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(
    coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif()



add_subdirectory(deps)
add_subdirectory(src)


include(CTest)

if(BUILD_TESTING)
  target_compile_definitions(unity PRIVATE UNITY_INCLUDE_PRINT_FORMATTED UNITY_OUTPUT_COLOR)
  add_subdirectory(tests)
endif()
