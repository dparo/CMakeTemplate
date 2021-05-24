set(
  TEST_SOURCES_LIST
  "helloworld.c"
)

foreach(SRC IN LISTS TEST_SOURCES_LIST)
  get_filename_component(TARGET "${SRC}" NAME_WE)

  add_executable("${TARGET}" "${SRC}")
  target_link_libraries("${TARGET}" PRIVATE unity)
  target_include_directories("${TARGET}" PRIVATE ./ ../src)

  target_compile_definitions("${TARGET}" PRIVATE UNITY_INCLUDE_PRINT_FORMATTED UNITY_OUTPUT_COLOR)

  if(UNIX AND NOT APPLE)
    target_compile_definitions("${TARGET}" PRIVATE _GNU_SOURCE)
  endif()

  add_test(
    NAME "${TARGET}" COMMAND "${TARGET}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  )
endforeach()
