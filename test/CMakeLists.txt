find_package(Catch2 REQUIRED)
find_package(docopt CONFIG)
find_package(fmt CONFIG)
find_package(spdlog CONFIG)

include(CTest)
include(Catch)

add_library(catch_main OBJECT catch_main.cpp)
target_link_libraries(
  catch_main
  PUBLIC Catch2::Catch2
         docopt::docopt
         fmt::fmt
	 spdlog::spdlog)
target_link_libraries(catch_main PRIVATE project_options)

# Provide a simple smoke test to make sure that the CLI works and can display a --help message
add_test(NAME cli.has_help COMMAND intro --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND intro --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

add_test(NAME cli.add COMMAND intro add 4 5)
set_tests_properties(cli.add PROPERTIES PASS_REGULAR_EXPRESSION "9")

add_test(NAME cli.add_bad COMMAND intro add 4 hello)
set_tests_properties(cli.add_bad PROPERTIES PASS_REGULAR_EXPRESSION "not an integer")

add_test(NAME cli.mult COMMAND intro mult 4 5)
set_tests_properties(cli.mult PROPERTIES PASS_REGULAR_EXPRESSION "20")

add_test(NAME cli.mult_bad COMMAND intro mult 4 hello)
set_tests_properties(cli.mult_bad PROPERTIES PASS_REGULAR_EXPRESSION "not an integer")

add_test(NAME cli.flaky_add COMMAND intro flaky_add 1073741823 1)
set_tests_properties(cli.flaky_add PROPERTIES PASS_REGULAR_EXPRESSION "-1073741824")

add_test(NAME cli.flaky_add_bad COMMAND intro flaky_add 4 hello)
set_tests_properties(cli.flaky_add_bad PROPERTIES PASS_REGULAR_EXPRESSION "not an integer")

add_test(NAME cli.bad_command COMMAND intro bad_command)
set_tests_properties(cli.bad_command PROPERTIES PASS_REGULAR_EXPRESSION "Arguments did not match expected patterns")

if(ENABLE_DEVELOPER_MODE)
    # These tests can only run when the sanitizers are enabled
    add_test(NAME cli.leak COMMAND intro leak)
    set_tests_properties(cli.leak PROPERTIES PASS_REGULAR_EXPRESSION "detected memory leaks")

    add_test(NAME cli.bound COMMAND intro bound)
    set_tests_properties(cli.bound PROPERTIES PASS_REGULAR_EXPRESSION "buffer-overflow")

    add_test(NAME cli.signed_overflow COMMAND intro signed_overflow)
    set_tests_properties(cli.signed_overflow PROPERTIES PASS_REGULAR_EXPRESSION "signed integer overflow")
endif()

add_executable(tests test_ops.cpp test_parse_args.cpp)
target_sources(tests PRIVATE ../src/ops.cpp ../src/parse_args.cpp)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main)
target_include_directories(tests PRIVATE ../src)
target_link_directories(tests PRIVATE ../src)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
  tests
  TEST_PREFIX
  "unittests."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)

# Add a file containing a set of constexpr tests
add_executable(constexpr_tests constexpr_tests.cpp)
target_link_libraries(constexpr_tests PRIVATE project_options project_warnings catch_main)
target_include_directories(constexpr_tests PRIVATE ../src)
target_link_directories(constexpr_tests PRIVATE ../src)

catch_discover_tests(
  constexpr_tests
  TEST_PREFIX
  "constexpr."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "constexpr."
  OUTPUT_SUFFIX
  .xml)

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
add_executable(relaxed_constexpr_tests constexpr_tests.cpp)
target_link_libraries(relaxed_constexpr_tests PRIVATE project_options project_warnings catch_main)
target_compile_definitions(relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
target_include_directories(relaxed_constexpr_tests PRIVATE ../src)
target_link_directories(relaxed_constexpr_tests PRIVATE ../src)

catch_discover_tests(
  relaxed_constexpr_tests
  TEST_PREFIX
  "relaxed_constexpr."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "relaxed_constexpr."
  OUTPUT_SUFFIX
  .xml)
