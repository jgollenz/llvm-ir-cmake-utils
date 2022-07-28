# cmake file

# options

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath /lib")

# general defs

set(SOURCES
  foo.cpp)


# directory level

add_subdirectory(./lib)

# target level

add_executable(foo ${SOURCES})

# this property is required by our parasitic targets
set_target_properties(foo PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(foo bar_bc_lib)
target_include_directories(foo PUBLIC "./include")

target_compile_options(foo PUBLIC "-O0")

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "5.0.0" OR
    CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "5.0.0")
  target_compile_options(foo PUBLIC -Xclang -disable-O0-optnone)
endif()

set_target_properties(foo PROPERTIES
  CXX_STANDARD 11
  CXX_EXTENSIONS OFF)

# attachments on first target

llvmir_attach_bc_target(foo_bc foo)

llvmir_attach_opt_pass_target(foo_pass1 foo_bc -mem2reg)
llvmir_attach_opt_pass_target(foo_pass2 foo_pass1 -simplifycfg -licm)
llvmir_attach_opt_pass_target(foo_pass3 foo_pass2 -licm)

llvmir_attach_disassemble_target(foo_dis foo_pass2)
llvmir_attach_assemble_target(foo_as foo_dis)

llvmir_attach_link_target(foo_llvmlink foo_pass2)

llvmir_attach_opt_pass_target(foo_pass4 foo_llvmlink -simplifycfg)

llvmir_attach_executable(foo_bc_exe foo_pass2 SHARED)


