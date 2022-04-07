find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)

# Generic test that uses conan libs
add_executable(intro main.cpp leak.cpp)

#set_source_files_properties(leak.cpp PROPERTIES COMPILE_OPTIONS -Wno-error=memleak -Wno-error=unreadVariable -Wno-error=unusedAllocatedMemory)
set_source_files_properties(leak.cpp PROPERTIES COMPILE_OPTIONS -Wno-error=array-bounds)

target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)

target_include_directories(intro PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
