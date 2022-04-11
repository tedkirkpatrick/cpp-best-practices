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


static constexpr auto USAGE =
  R"(Demonstrate C++ build and test.

    Usage:
          intro add <int_a> <int_b>
          intro mult <int_a> <int_b>
          intro leak
          intro bound
          intro signed_overflow
          intro flaky_add <int_a> <int_b>
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
    else {
      // The call to docopt above should have caught every other case
      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
      assert(false);
    }
  } catch (const std::exception &e) {
    fmt::print("Unhandled exception in main: {}\n", e.what());
  }
}
