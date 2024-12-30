cmake_minimum_required(VERSION 3.29)
project(Imklib C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
file(GLOB_RECURSE IMKLIB_SOURCES "src/*.c")

add_compile_options(
  -g3 -ggdb
  -fsanitize=address,undefined,leak,null,alignment
  -Wall -Wextra -pedantic -Wparentheses -Wformat=2
  -Wshadow -Wwrite-strings -Wredundant-decls -Wmissing-include-dirs
  -pedantic-errors -Wuninitialized -Wmissing-declarations -Wconversion
  -Wdouble-promotion -Wfloat-equal -Wmain -Wundef
  -Wstrict-prototypes -Wnested-externs -Wold-style-definition
  -Wbad-function-cast -Wno-unknown-pragmas -Wno-unused-function
  -fno-strict-aliasing
)
add_link_options(-fsanitize=address,undefined,leak,null,alignment)

# Set the output directory for the library
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Create the static library
add_library(imklib STATIC ${IMKLIB_SOURCES})

# Set the base output directory for the examples
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

# Variables to store example targets
set(EXAMPLES_TARGETS "")

# Compile and link .c files in one-level subdirectories
file(GLOB EXAMPLE_SUBDIRS RELATIVE "${CMAKE_SOURCE_DIR}/examples" "${CMAKE_SOURCE_DIR}/examples/*")
foreach(SUBDIR ${EXAMPLE_SUBDIRS})
  if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/examples/${SUBDIR}")
    # Get all .c files in the subdirectory
    file(GLOB SUBDIR_SOURCES "${CMAKE_SOURCE_DIR}/examples/${SUBDIR}/*.c")
    
    if(SUBDIR_SOURCES)
      # Define the output binary name as the folder name
      add_executable(${SUBDIR} ${SUBDIR_SOURCES})
      target_link_libraries(${SUBDIR} imklib)
      
      # Set the output directory for the binary to the same subdirectory
      set_target_properties(${SUBDIR} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${SUBDIR}"
      )
      
      # Add to examples target
      list(APPEND EXAMPLES_TARGETS ${SUBDIR})
    endif()
  endif()
endforeach()

# Compile and link .c files directly inside examples directory
file(GLOB DIRECT_EXAMPLES "${CMAKE_SOURCE_DIR}/examples/*.c")
foreach(EXAMPLE_FILE ${DIRECT_EXAMPLES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
  
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
  target_link_libraries(${EXAMPLE_NAME} imklib)
  
  # Set the output directory for the binary to the examples directory
  set_target_properties(${EXAMPLE_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
  )
  
  # Add to examples target
  list(APPEND EXAMPLES_TARGETS ${EXAMPLE_NAME})
endforeach()

# Custom target to build all examples
add_custom_target(examples DEPENDS ${EXAMPLES_TARGETS})

