# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#

find_package(fmt)
find_package(spdlog CONFIG)

add_executable(fuzz_tester fuzz_tester.cpp)
target_link_libraries(
  fuzz_tester
  PRIVATE project_options
          project_warnings
          fmt::fmt
          spdlog::spdlog
          -coverage
          -fsanitize=fuzzer,undefined,address)
target_sources(fuzz_tester PRIVATE ../src/ops.cpp ../src/sandemo.cpp)
target_compile_options(fuzz_tester PRIVATE -fsanitize=fuzzer,undefined,address)
target_include_directories(fuzz_tester PRIVATE ../src "${CMAKE_BINARY_DIR}/configured_files/include")
target_link_directories(fuzz_tester PRIVATE ../src)

# sandemo.cpp requires special options because it demonstrates bad coding
# Turn off array-bounds checking by the compiler so that the address sanitizer can catch it
# Set sanitizer to exit on undefined behaviour
# Set '-O0' so that optimizer does not cull the useless allocation
set_source_files_properties(../src/sandemo.cpp PROPERTIES COMPILE_OPTIONS "-Wno-error=array-bounds;-fno-sanitize-recover;-O0")

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME fuzz_tester_run COMMAND fuzz_tester -max_total_time=${FUZZ_RUNTIME})
