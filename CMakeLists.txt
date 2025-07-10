cmake_minimum_required(VERSION 3.29)
project(Imklib C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set output directories
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

include_directories(include)
file(GLOB_RECURSE IMKLIB_SOURCES "src/*.c")

# Create the static library
add_library(imklib STATIC ${IMKLIB_SOURCES})

# Common warning flags
set(COMMON_WARNINGS
  -Wall -Wextra -pedantic -Wparentheses -Wformat=2
  -Wshadow -Wwrite-strings -Wredundant-decls -Wmissing-include-dirs
  -pedantic-errors -Wuninitialized -Wmissing-declarations -Wconversion
  -Wdouble-promotion -Wfloat-equal -Wmain -Wundef
  -Wstrict-prototypes -Wnested-externs -Wold-style-definition
  -Wbad-function-cast -Wno-unknown-pragmas -Wno-unused-function
  -fno-strict-aliasing
)

# Apply mode-specific flags to imklib
target_compile_options(imklib PRIVATE
  ${COMMON_WARNINGS}
  $<$<CONFIG:Debug>:
    -g3 -ggdb
    -fsanitize=address,undefined,leak,null,alignment
  >
  $<$<CONFIG:Release>:-O3>
)

target_link_options(imklib PRIVATE
  $<$<CONFIG:Debug>:-fsanitize=address,undefined,leak,null,alignment>
)

# Helper to apply sanitizer flags to example targets
function(enable_sanitizers target)
  target_compile_options(${target} PRIVATE
    ${COMMON_WARNINGS}
    $<$<CONFIG:Debug>:
      -g3 -ggdb
      -fsanitize=address,undefined,leak,null,alignment
    >
    $<$<CONFIG:Release>:-O3>
  )
  target_link_options(${target} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined,leak,null,alignment>
  )
endfunction()

# =====================
# = Subdirectory Examples =
# =====================
set(EXAMPLES_TARGETS "")
file(GLOB EXAMPLE_SUBDIRS RELATIVE "${CMAKE_SOURCE_DIR}/examples" "${CMAKE_SOURCE_DIR}/examples/*")

foreach(SUBDIR ${EXAMPLE_SUBDIRS})
  if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/examples/${SUBDIR}")
    file(GLOB SUBDIR_SOURCES "${CMAKE_SOURCE_DIR}/examples/${SUBDIR}/*.c")

    if(SUBDIR_SOURCES)
      add_executable(${SUBDIR} ${SUBDIR_SOURCES})
      target_link_libraries(${SUBDIR} imklib)
      enable_sanitizers(${SUBDIR})

      set_target_properties(${SUBDIR} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${SUBDIR}"
      )

      list(APPEND EXAMPLES_TARGETS ${SUBDIR})
    endif()
  endif()
endforeach()

# =====================
# = Top-level Examples =
# =====================
file(GLOB DIRECT_EXAMPLES "${CMAKE_SOURCE_DIR}/examples/*.c")

foreach(EXAMPLE_FILE ${DIRECT_EXAMPLES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
  target_link_libraries(${EXAMPLE_NAME} imklib)
  enable_sanitizers(${EXAMPLE_NAME})

  set_target_properties(${EXAMPLE_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
  )

  list(APPEND EXAMPLES_TARGETS ${EXAMPLE_NAME})
endforeach()

# Group all examples under a single target
add_custom_target(examples DEPENDS ${EXAMPLES_TARGETS})

