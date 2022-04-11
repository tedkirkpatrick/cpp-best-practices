find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)

# Generic test that uses conan libs
add_executable(intro main.cpp sandemo.cpp ops.cpp)

# sandemo.cpp requires special options because it demonstrates bad coding
# Turn off array-bounds checking by the compiler so that the address sanitizer can catch it
# Set sanitizer to exit on undefined behaviour
# Set '-O0' so that optimizer does not cull the useless allocation
set_source_files_properties(sandemo.cpp PROPERTIES COMPILE_OPTIONS "-Wno-error=array-bounds;-fno-sanitize-recover;-O0")

target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog
	  -fno-sanitize-recover)

target_include_directories(intro PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
