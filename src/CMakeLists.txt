if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set(WARN_FLAGS "-Wall -Wextra")
  string(APPEND CMAKE_C_FLAGS " ${WARN_FLAGS}")
  string(APPEND CMAKE_CXX_FLAGS " ${WARN_FLAGS}")
endif()

add_executable(clex main.c)
