# cmake file

# options

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath /lib")

# general defs

set(SOURCES
  baz.cpp)


# directory level


# target level

add_library(baz ${SOURCES})

# this property is required by our parasitic targets
set_target_properties(baz PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(baz PUBLIC "../../include")

target_compile_options(baz PUBLIC "-O0")

set_target_properties(baz PROPERTIES
  CXX_STANDARD 11
  CXX_EXTENSIONS OFF)

