if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set(WARN_FLAGS "-Wall -Wextra -Wunused")
  string(APPEND CMAKE_C_FLAGS " ${WARN_FLAGS}")
  string(APPEND CMAKE_CXX_FLAGS " ${WARN_FLAGS}")
  string(APPEND CMAKE_LINKER_FLAGS " ${WARN_FLAGS}")
endif()

add_executable(a.out main.c)
target_include_directories(a.out PRIVATE ./)
