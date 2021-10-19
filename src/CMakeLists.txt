if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(WARN_FLAGS "-Wall -Wextra -Wunused")
    string(APPEND CMAKE_C_FLAGS " ${WARN_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS " ${WARN_FLAGS}")
    string(APPEND CMAKE_LINKER_FLAGS " ${WARN_FLAGS}")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(NOWARN_FLAGS "-Wno-unused-parameter")
        string(APPEND CMAKE_C_FLAGS " ${NOWARN_FLAGS}")
        string(APPEND CMAKE_CXX_FLAGS " ${NOWARN_FLAGS}")
        string(APPEND CMAKE_LINKER_FLAGS " ${NOWARN_FLAGS}")
    endif()
endif()



find_package(Git REQUIRED)

execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_SHA1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

# the date of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_DATE
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

# the subject of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%s
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

# generate version.c
configure_file("${CMAKE_SOURCE_DIR}/src/version.c.in" "${CMAKE_BINARY_DIR}/src/version.c" @ONLY)


add_library(libmain sum.c)
target_include_directories(libmain PUBLIC ./)
target_link_libraries(libmain PUBLIC logc)

add_executable(cptp main.c)
target_link_libraries(cptp PRIVATE libmain)
target_link_libraries(cptp PRIVATE argtable3)
target_include_directories(cptp PRIVATE "${DEPS_DIR}/argtable3/src")
