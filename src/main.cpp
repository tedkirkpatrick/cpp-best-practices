#include <cassert>
#include <functional>
#include <iostream>

#include <docopt/docopt.h>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include "ops.hpp"
#include "sandemo.hpp"

#include "parse_args.hpp"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `cpp_best_practices`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>


//--- Begin simulated security error

// This section of code can be used to generate a CodeQL Critical / DescriptorMayNotBeClosed
// alert from the GitHub CodeQL Security Check.
// The code for this check is at
// https://github.com/github/codeql/blob/main/cpp/ql/src/Critical/DescriptorMayNotBeClosed.ql

// We simulate a function that can deallocate a socket descriptor in a local variable
// without first closing it.  The CodeQL query above checks for a specific coding
// pattern, which we implement in descriptor_may_not_be_closed().
// If the function's call to close() is commented out, the query will succeed
// and an alert will be issued.

// Stub for actual socket creation call.  CodeQl only look at name,
// not its actual code. See code for 'predicate allocateDescriptorCall()' at
// https://github.com/github/codeql/blob/b433f08cef9038d60e2bdf50bfedaf112f35d3f6/cpp/ql/lib/semmle/code/cpp/pointsto/PointsTo.qll#L699
int socket (int checkVal) {
  return checkVal;
}

// close() already declared in /usr/include/unistd.h, included by one of above headers

// Routine with a potential close error
int descriptor_may_not_be_closed(int checkVal) {
  auto logger = spdlog::get("logger");
  if (logger) {logger->error("A simulated socket may not be closed before this program's end");}

  int sockfd = socket(checkVal);
  if (sockfd != -1) {
    // Comment out the following line to generate a GitHub CodeQL Security Alert
    close(sockfd);
    return 0;
  }
  // If we had actually opened a socket, our caller would be required
  // to call close on this result. In this case, no socket was opened,
  // so the caller can simply ignore it.
  return sockfd;
}

//--- End simulated security error

static constexpr auto USAGE =
  R"(Demonstrate C++ build and test.

    Usage:
          intro add <int_a> <int_b>
          intro mult <int_a> <int_b>
          intro leak
          intro bound
          intro signed_overflow
          intro flaky_add <int_a> <int_b>
          intro may_not_close_socket
          intro (-h | --help)
          intro --version
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

int main(int argc, const char **argv)
{
  try {
    auto logger = spdlog::stdout_color_mt("logger");

    parse_args::ArgMap args = docopt::docopt(USAGE,
      { std::next(argv), std::next(argv, argc) },
      true,// show help if requested
      fmt::format("{} {}",
        cpp_best_practices::cmake::project_name,
        cpp_best_practices::cmake::project_version));// version string, acquired from config.hpp via CMake

    if (args.at("add").asBool()) {
      auto [valid, a, b] = parse_args::getTwoInts(args);
      if (valid) {
	fmt::print("{} + {} = {}\n",
		   a,
		   b,
		   ops::add(a, b));
      }
    }
    else if (args.at("mult").asBool()) {
      auto [valid, a, b] = parse_args::getTwoInts(args);
      if (valid) {
	fmt::print("{} * {} = {}\n",
		   a,
		   b,
		   ops::mult(a, b));
      }
    }
    else if (args.at("flaky_add").asBool()) {
      auto [valid, a, b] = parse_args::getTwoInts(args);
      if (valid) {
	fmt::print("{} + {} = {}\n",
		   a,
		   b,
		   ops::flaky_add(a, b));
      }
    }
    else if (args.at("leak").asBool()) {
      sandemo::leak_memory();
    }
    else if (args.at("bound").asBool()) {
      sandemo::bound();
    }
    else if (args.at("signed_overflow").asBool()) {
      (void) sandemo::signed_overflow(1);
    }
    else if (args.at("may_not_close_socket").asBool()) {
      (void) descriptor_may_not_be_closed(argc);
    }
    else {
      // The call to docopt above should have caught every other case
      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
      assert(false);
    }
  } catch (const std::exception &e) {
    fmt::print("Unhandled exception in main: {}\n", e.what());
  }
}
