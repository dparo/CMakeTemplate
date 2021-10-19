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


add_library(libmain sum.c)
target_include_directories(libmain PUBLIC ./)
target_link_libraries(libmain PUBLIC logc)

add_executable(cptp main.c)
target_link_libraries(cptp PRIVATE libmain)
target_link_libraries(cptp PRIVATE argtable3)
