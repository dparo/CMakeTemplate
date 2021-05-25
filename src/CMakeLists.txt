if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set(WARN_FLAGS "-Wall -Wextra -Wunused")
  string(APPEND CMAKE_C_FLAGS " ${WARN_FLAGS}")
  string(APPEND CMAKE_CXX_FLAGS " ${WARN_FLAGS}")
  string(APPEND CMAKE_LINKER_FLAGS " ${WARN_FLAGS}")
endif()


add_library(main sum.c)
target_include_directories(main PUBLIC ./)

add_executable(a.out main.c)
target_link_libraries(a.out PRIVATE main)
